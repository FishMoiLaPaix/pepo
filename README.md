Cardboard SDK
=============
<<<<<<< HEAD
Copyright 2019 Google LLC
=======
Copyright 2019 Google LLC.  All rights reserved.
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)

This SDK provides everything you need to create your own Virtual Reality (VR)
experiences for Google Cardboard. It supports essential VR features, such as:

<<<<<<< HEAD
 * Motion tracking
 * Stereoscopic rendering
 * User interaction via the viewer button
=======
 * motion tracking
 * stereoscopic rendering
 * user interaction via the viewer button
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)

With these capabilities you can build entirely new VR experiences, or enhance
existing apps with VR capabilities.


## Get started

To get started with the Cardboard SDK, see:

* [Quickstart for Android NDK](//developers.google.com/cardboard/develop/c/quickstart)
* [Quickstart for iOS](//developers.google.com/cardboard/develop/ios/quickstart)


## API reference

<<<<<<< HEAD
* [Cardboard SDK API Reference for Android NDK and iOS](//developers.google.com/cardboard/reference/c)
=======
* [Cardboard SDK API Reference for Android NDK](//developers.google.com/cardboard/reference/c)
* [Cardboard SDK API Reference for iOS](//developers.google.com/cardboard/reference/ios)

>>>>>>> 5f55cf9 (Cardboard SDK initial release.)

## Release notes

The SDK release notes are available on the
[releases](//github.com/googlevr/cardboard/releases) page.


<<<<<<< HEAD
## Roadmap

The project roadmap is available on the
[Projects](https://github.com/googlevr/cardboard/projects/1) page.


=======
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
## How to make contributions

Please read and follow the steps in [CONTRIBUTING.md](/CONTRIBUTING.md) file.


## License

Please see the [LICENSE](/LICENSE) file.

<<<<<<< HEAD
## Data Collection

The libraries `cardboard` and `cardboard-xr-plugin` do not collect any data.
However, when a QR code is recognized during scanning as requested by the
developer, these libraries may make multiple web requests to retrieve the
Cardboard viewer device parameters.

Specifically:

*   If the decoded URL matches "https://google.com/cardboard" or
    "https://google.com/cardboard/cfg?p=...", it is parsed to retrieve the
    Cardboard viewer device parameters.
*   Otherwise, the decoded URL is requested via a normal web request. Any HTTP
    redirects are followed until a matching URL is found.

See
[QrCodeContentProcessor.java](sdk/qrcode/android/java/com/google/cardboard/sdk/qrcode/QrCodeContentProcessor.java)
(Android) and
[device_params_helper.mm](sdk/qrcode/ios/device_params_helper.mm) (iOS) for the
code that does the above.
=======
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)

## Brand guidelines

The "Google Cardboard" name is a trademark owned by Google and is not included
<<<<<<< HEAD
within the assets licensed under the Apache License 2.0. Cardboard is a free
and open-source SDK that developers can use to create apps that are compatible
with the Google Cardboard VR platform. At the same time, it's important to make
sure that people don't use the "Google Cardboard" mark in ways that could
create confusion.

The guidelines below are designed to clarify the permitted uses of the "Google
Cardboard" mark.
=======
within the assets licensed under the Apache License 2.0.

It's important to make sure that you don't use the "Google Cardboard" mark in
ways that could create confusion. The guidelines below are designed to clarify
the permitted uses of the "Google Cardboard" mark.
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)

**Things you can do**:

* Use the "Google Cardboard" mark to describe or refer to apps developed with
<<<<<<< HEAD
  the Cardboard SDK in ways that would be considered "fair use."
* Use the "Google Cardboard" mark to make truthful factual statements regarding
  the compatibility or interoperability of your app. For example, "This app is
  compatible with Google Cardboard" or "This app works with Google Cardboard."
=======
  the Cardboard SDK in ways that would be considered "fair use".
* Use the "Google Cardboard" mark to make truthful factual statements regarding
  the compatibility or interoperability of your app. For example, "This app is
  compatible with Google Cardboard" or "This app works with Google Cardboard".
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)

**Things you can't do**:

* Don't use the "Google Cardboard" mark in a manner that implies that Google has
  endorsed or authorized your app or that makes your app appear to be an
  official Google product. For example, you shouldn't reference your product as
<<<<<<< HEAD
  "an official Google Cardboard app."
* Don't incorporate the "Google Cardboard" mark into your own product names,
  service names, trademarks, logos, or company names.
* Don't display the "Google Cardboard" mark in a manner that is misleading,
  unfair, defamatory, infringing, libelous, disparaging, obscene or otherwise
  objectionable to Google.
* Don't alter or distort the "Google Cardboard" mark. This includes modifying
  the mark through hyphenation, combination or abbreviation. For example, don't
  say "G Cardboard" or "Google-Cardboard."

In addition to these guidelines, please ensure that you follow the trademark
usage guidelines available here:
https://www.google.com/permissions/logos-trademarks/.

## Manufacturers
The [Cardboard viewer
specification](https://developers.google.com/cardboard/manufacturers) is
open source and ready for you to start building.
=======
  "an official Google Cardboard app".
* Don't incorporate the "Google Cardboard" mark into your own product names,
  service names, trademarks, logos, or company names.
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
