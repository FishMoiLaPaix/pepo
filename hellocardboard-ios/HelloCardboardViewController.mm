/*
<<<<<<< HEAD
 * Copyright 2019 Google LLC
=======
 * Copyright 2019 Google LLC. All Rights Reserved.
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#import "HelloCardboardViewController.h"

#import "HelloCardboardOverlayView.h"
#import "HelloCardboardRenderer.h"
#import "cardboard.h"

@interface HelloCardboardViewController () <GLKViewControllerDelegate, HelloCardboardOverlayViewDelegate> {
  CardboardLensDistortion *_cardboardLensDistortion;
  CardboardHeadTracker *_cardboardHeadTracker;
  std::unique_ptr<cardboard::hello_cardboard::HelloCardboardRenderer> _renderer;
<<<<<<< HEAD

  // This counter keeps track of the successful device parameters save operations count.
  int _deviceParamsChangedCount;
=======
  BOOL _isPaused;
  BOOL _updateParams;
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
}
@end

@implementation HelloCardboardViewController

- (void)dealloc {
  CardboardLensDistortion_destroy(_cardboardLensDistortion);
  CardboardHeadTracker_destroy(_cardboardHeadTracker);
}

- (void)viewDidLoad {
  [super viewDidLoad];

  self.delegate = self;

  // Create an overlay view on top of the GLKView.
  HelloCardboardOverlayView *overlayView = [[HelloCardboardOverlayView alloc] initWithFrame:self.view.bounds];
  overlayView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
  overlayView.delegate = self;
  [self.view addSubview:overlayView];

  // Add a tap gesture to handle viewer trigger action.
  UITapGestureRecognizer *tapGesture =
      [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(didTapGLView:)];
  [self.view addGestureRecognizer:tapGesture];

  // Prevents screen to turn off.
  UIApplication.sharedApplication.idleTimerDisabled = YES;

  // Create an OpenGL ES context and assign it to the view loaded from storyboard
  GLKView *glkView = (GLKView *)self.view;
  glkView.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];

  // Set animation frame rate.
  self.preferredFramesPerSecond = 60;

  // Set the GL context.
  [EAGLContext setCurrentContext:glkView.context];

  // Make sure the glkView has bound its offscreen buffers before calling into cardboard.
  [glkView bindDrawable];

  // Create cardboard head tracker.
  _cardboardHeadTracker = CardboardHeadTracker_create();
  _cardboardLensDistortion = nil;
<<<<<<< HEAD

  // Set the counter to -1 to force a device params update.
  _deviceParamsChangedCount = -1;
=======
  _updateParams = YES;
  _isPaused = NO;
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
}

- (void)viewDidAppear:(BOOL)animated {
  [super viewDidAppear:animated];
  if (@available(iOS 11.0, *)) {
    [self setNeedsUpdateOfHomeIndicatorAutoHidden];
  }
<<<<<<< HEAD
  [self resumeCardboard];
=======
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
}

- (BOOL)prefersHomeIndicatorAutoHidden {
  return true;
}

- (UIInterfaceOrientationMask)supportedInterfaceOrientations {
  // Cardboard only supports landscape right orientation for inserting the phone in the viewer.
  return UIInterfaceOrientationMaskLandscapeRight;
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
<<<<<<< HEAD
  if (![self updateDeviceParams]) {
=======
  if (_updateParams) {
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
    return;
  }

  _renderer->DrawFrame();
}

- (void)glkViewControllerUpdate:(GLKViewController *)controller {
  // Perform GL state update before drawing.
}

<<<<<<< HEAD
- (BOOL)deviceParamsChanged {
  return _deviceParamsChangedCount != CardboardQrCode_getDeviceParamsChangedCount();
}

- (BOOL)updateDeviceParams {
  // Check if device parameters have changed.
  if (![self deviceParamsChanged]) {
    return YES;
  }

=======
- (void)glkViewController:(GLKViewController *)controller willPause:(BOOL)pause {
  // Doesn't execute the lifecycle code if it's not changing its state.
  if (_isPaused == pause) {
    return;
  }
  _isPaused = pause;

  if (pause) {
    CardboardHeadTracker_pause(_cardboardHeadTracker);
  } else {
    if (_updateParams) {
      [self updateCardboardParams];
    }
    CardboardHeadTracker_resume(_cardboardHeadTracker);
  }
}

- (void)updateCardboardParams {
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
  uint8_t *encodedDeviceParams;
  int size;
  CardboardQrCode_getSavedDeviceParams(&encodedDeviceParams, &size);

<<<<<<< HEAD
  if (size == 0) {
    return NO;
  }

  // Using native scale as we are rendering directly to the screen.
  CGRect screenRect = self.view.bounds;
  CGFloat screenScale = UIScreen.mainScreen.nativeScale;
  int height = screenRect.size.height * screenScale;
  int width = screenRect.size.width * screenScale;

  // Rendering coordinates asumes landscape orientation.
  if (height > width) {
    int temp = height;
    height = width;
    width = temp;
  }

  // Create CardboardLensDistortion.
  CardboardLensDistortion_destroy(_cardboardLensDistortion);
  _cardboardLensDistortion =
      CardboardLensDistortion_create(encodedDeviceParams, size, width, height);

  // Initialize HelloCardboardRenderer.
  _renderer.reset(new cardboard::hello_cardboard::HelloCardboardRenderer(
      _cardboardLensDistortion, _cardboardHeadTracker, width, height));
  _renderer->InitializeGl();

  CardboardQrCode_destroy(encodedDeviceParams);

  _deviceParamsChangedCount = CardboardQrCode_getDeviceParamsChangedCount();

  return YES;
}

- (void)pauseCardboard {
  self.paused = true;
  CardboardHeadTracker_pause(_cardboardHeadTracker);
}

- (void)resumeCardboard {
  // Check for device parameters existence in app storage. If they're missing,
  // we must scan a Cardboard QR code and save the obtained parameters.
  uint8_t *buffer;
  int size;
  CardboardQrCode_getSavedDeviceParams(&buffer, &size);
  if (size == 0) {
    [self switchViewer];
  }
  CardboardQrCode_destroy(buffer);

  CardboardHeadTracker_resume(_cardboardHeadTracker);
  self.paused = false;
}

- (void)switchViewer {
  CardboardQrCode_scanQrCodeAndSaveDeviceParams();
=======
  if (size != 0) {
    // Using native scale as we are rendering directly to the screen.
    CGRect screenRect = self.view.bounds;
    CGFloat screenScale = UIScreen.mainScreen.nativeScale;
    int height = screenRect.size.height * screenScale;
    int width = screenRect.size.width * screenScale;

    // Rendering coordinates asumes landscape orientation.
    if (height > width) {
      int temp = height;
      height = width;
      width = temp;
    }

    // Create CardboardLensDistortion.
    CardboardLensDistortion_destroy(_cardboardLensDistortion);
    _cardboardLensDistortion =
        CardboardLensDistortion_create(encodedDeviceParams, size, width, height);

    // Initialize HelloCardboardRenderer.
    _renderer.reset(new cardboard::hello_cardboard::HelloCardboardRenderer(_cardboardLensDistortion,
                                                             _cardboardHeadTracker, width, height));
    _renderer->InitializeGl();
    _updateParams = NO;
  } else {
    _updateParams = YES;
    [self didChangeViewerProfile];
  }
  CardboardQrCode_destroy(encodedDeviceParams);
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
}

- (void)didTapGLView:(id)sender {
  if (_renderer != NULL) {
    _renderer->OnTriggerEvent();
  }
}

- (void)didTapBackButton {
  // User pressed the back button. Pop this view controller.
  NSLog(@"User pressed back button");
}

- (void)didPresentSettingsDialog:(BOOL)presented {
  // The overlay view is presenting the settings dialog. Pause our rendering while presented.
  self.paused = presented;
}

- (void)didChangeViewerProfile {
<<<<<<< HEAD
  [self pauseCardboard];
  [self switchViewer];
  [self resumeCardboard];
=======
  CardboardQrCode_scanQrCodeAndSaveDeviceParams();
  _updateParams = YES;
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
}

@end
