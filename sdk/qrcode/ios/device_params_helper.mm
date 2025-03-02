/*
<<<<<<< HEAD
 * Copyright 2019 Google LLC
=======
 * Copyright 2019 Google Inc. All Rights Reserved.
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#import "qrcode/ios/device_params_helper.h"

#include <string>
#include <vector>

#include "qrcode/cardboard_v1/cardboard_v1.h"
<<<<<<< HEAD
#import "qrcode/ios/nsurl_session_data_handler.h"

=======
#import "qrcode/ios/nsurl_connection_data_handler.h"

static NSString *const kCardboardDeviceParamsUrlPrefix = @"http://google.com/cardboard/cfg";
static NSString *const kOriginalCardboardDeviceParamsUrl = @"http://g.co/cardboard";
static NSString *const kDeviceParamsDataIdentifier = @"kDeviceParamsDataIdentifier";
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
// The value is an array with the creation time and the device params data.
static NSString *const kCardboardDeviceParamsAndTimeKey =
    @"com.google.cardboard.sdk.DeviceParamsAndTime";

@implementation CardboardDeviceParamsHelper

+ (NSData *)parseURL:(NSURL *)url {
  if (!url) {
    return nil;
  }
<<<<<<< HEAD

  if ([NSURLSessionDataHandler isOriginalCardboardDeviceUrl:url]) {
    return [CardboardDeviceParamsHelper createCardboardV1Params];
  } else if ([NSURLSessionDataHandler isCardboardDeviceUrl:url]) {
    return [CardboardDeviceParamsHelper readDeviceParamsFromUrl:url];
  }

=======
  // If URI is recognized as original cardboard device, use the default proto values.
  if ([kOriginalCardboardDeviceParamsUrl isEqualToString:url.absoluteString]) {
    return [CardboardDeviceParamsHelper createCardboardV1Params];
  }

  NSURLComponents *urlComponents = [NSURLComponents componentsWithURL:url
                                              resolvingAgainstBaseURL:NO];
  NSString *rawDeviceConfig = nil;
  for (NSURLQueryItem *queryItem in urlComponents.queryItems) {
    // Device parameters decoded data is after the p paramers in the url, for example:
    // http://google.com/cardboard/cfg?p=device_param_encoded_string.
    if ([queryItem.name isEqualToString:@"p"]) {
      rawDeviceConfig = queryItem.value;
      break;
    }
  }
  if (rawDeviceConfig) {
    rawDeviceConfig = [CardboardDeviceParamsHelper convertToNormalBase64String:rawDeviceConfig];
    NSData *decodedData = [[NSData alloc] initWithBase64EncodedString:rawDeviceConfig options:0];
    return decodedData;
  }
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
  return nil;
}

+ (void)readFromUrl:(NSURL *)url
     withCompletion:(void (^)(NSData *deviceParams, NSError *error))completion {
  NSMutableURLRequest *request =
      [NSMutableURLRequest requestWithURL:url
                              cachePolicy:NSURLRequestReloadIgnoringCacheData
                          timeoutInterval:10];

  // Save bandwidth, just read the header.
  [request setHTTPMethod:@"HEAD"];

<<<<<<< HEAD
  NSURLSessionDataHandler *dataHandler =
      [[NSURLSessionDataHandler alloc] initWithOnUrlCompletion:^(NSURL *targetUrl, NSError *error) {
        if (!targetUrl) {
          NSLog(@"failed to result the url = %@", url);
        }
        completion([CardboardDeviceParamsHelper parseURL:targetUrl], error);
      }];

  NSURLSessionConfiguration *config = [NSURLSessionConfiguration defaultSessionConfiguration];
  NSURLSession *session = [NSURLSession sessionWithConfiguration:config
                                                        delegate:dataHandler
                                                   delegateQueue:[NSOperationQueue mainQueue]];
  NSURLSessionDataTask *dataTask = [session dataTaskWithRequest:request];
  [dataTask resume];
=======
  CardboardNSURLConnectionDataHandler *dataHandler = [[CardboardNSURLConnectionDataHandler alloc]
      initWithOnUrlCompletion:^(NSURL *targetUrl, NSError *error) {
        if (!targetUrl) {
          // Retry loading the url with https scheme.
          NSURLComponents *components = [NSURLComponents componentsWithURL:url
                                                   resolvingAgainstBaseURL:NO];
          if ([components.scheme.lowercaseString isEqualToString:@"http"]) {
            components.scheme = @"https";
            NSURL *secureUrl = [components URL];
            [self readFromUrl:secureUrl withCompletion:completion];
            return;
          } else {
            NSLog(@"failed to result the url = %@", url);
          }
        }
        completion([CardboardDeviceParamsHelper parseURL:targetUrl], error);
      }];
  NSURLConnection *connection = [NSURLConnection connectionWithRequest:request
                                                              delegate:dataHandler];
  [connection start];
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
}

+ (void)resolveAndUpdateViewerProfileFromURL:(NSURL *)url
                              withCompletion:(void (^)(BOOL success, NSError *error))completion {
<<<<<<< HEAD
  // If the scheme is http, replace it with https.
  NSURLComponents *components = [NSURLComponents componentsWithURL:url resolvingAgainstBaseURL:NO];
  if ([components.scheme.lowercaseString isEqualToString:@"http"]) {
    components.scheme = @"https";
    url = [components URL];
  }

=======
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
  // Try to parse the url if it has the params encoded in it. This can help avoid a network call.
  NSData *viewerParams = [CardboardDeviceParamsHelper parseURL:url];
  if (viewerParams) {
    [CardboardDeviceParamsHelper update:viewerParams];
    completion(YES, nil);
  } else {
    [CardboardDeviceParamsHelper readFromUrl:url
                              withCompletion:^(NSData *deviceParams, NSError *error) {
                                if (deviceParams) {
                                  [CardboardDeviceParamsHelper update:deviceParams];
                                }
                                completion(deviceParams != nil, error);
                              }];
  }
}

+ (void)saveCardboardV1Params {
  NSData *deviceParams = [CardboardDeviceParamsHelper createCardboardV1Params];
  [CardboardDeviceParamsHelper update:deviceParams];
}

+ (NSData *)createCardboardV1Params {
  std::vector<uint8_t> deviceParams = cardboard::qrcode::getCardboardV1DeviceParams();
  return [NSData dataWithBytes:deviceParams.data() length:deviceParams.size()];
}

<<<<<<< HEAD
+ (NSData *)readDeviceParamsFromUrl:(NSURL *)url {
  NSURLComponents *urlComponents = [NSURLComponents componentsWithURL:url
                                              resolvingAgainstBaseURL:NO];
  for (NSURLQueryItem *queryItem in urlComponents.queryItems) {
    // Device parameters decoded data is after the p paramers in the url, for example:
    // https://google.com/cardboard/cfg?p=device_param_encoded_string.
    if ([queryItem.name isEqualToString:@"p"]) {
      NSString *encodedDeviceParams =
          [CardboardDeviceParamsHelper convertToNormalBase64String:queryItem.value];
      return [[NSData alloc] initWithBase64EncodedString:encodedDeviceParams options:0];
    }
  }

  NSLog(@"No Cardboard parameters in URL: %@", url);
  return nil;
}

=======
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
+ (void)update:(NSData *)deviceParams {
  [CardboardDeviceParamsHelper
      writeDeviceParams:std::string((char *)deviceParams.bytes, deviceParams.length)];
}

+ (NSData *)readSerializedDeviceParams {
  std::string deviceParams = [CardboardDeviceParamsHelper readDeviceParams];
  return [NSData dataWithBytes:deviceParams.c_str() length:deviceParams.length()];
}

// Convert the url safe base64 string into normal base64 string with padding if needed.
+ (NSString *)convertToNormalBase64String:(NSString *)original {
  original = [original stringByReplacingOccurrencesOfString:@"_" withString:@"/"];
  original = [original stringByReplacingOccurrencesOfString:@"-" withString:@"+"];
  // Add the padding with "=" if needed.
  NSUInteger paddingCount = 4 - (original.length % 4);
  if (paddingCount == 1) {
    original = [NSString stringWithFormat:@"%@=", original];
  } else if (paddingCount == 2) {
    original = [NSString stringWithFormat:@"%@==", original];
  } else if (paddingCount == 3) {
    original = [NSString stringWithFormat:@"%@===", original];
  }
  return original;
}

+ (std::string)readDeviceParams {
  NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
  NSArray *array = [defaults arrayForKey:kCardboardDeviceParamsAndTimeKey];
  NSData *serializedDeviceParams = array ? array[1] : nil;
  if (serializedDeviceParams) {
    return std::string((char *)serializedDeviceParams.bytes, serializedDeviceParams.length);
  } else {
    return std::string("");
  }
}

+ (bool)writeDeviceParams:(const std::string &)device_params {
  NSData *deviceParams = [NSData dataWithBytes:device_params.c_str() length:device_params.length()];
  NSArray *array = @[ [NSDate date], deviceParams ];
  [[NSUserDefaults standardUserDefaults] setObject:array forKey:kCardboardDeviceParamsAndTimeKey];
  return true;
}

@end
