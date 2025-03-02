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
#include "qrcode/cardboard_v1/cardboard_v1.h"

<<<<<<< HEAD
namespace cardboard::qrcode {

std::vector<uint8_t> getCardboardV1DeviceParams() {
  return {
      0xa,  0xc,  0x47, 0x6f, 0x6f, 0x67, 0x6c, 0x65, 0x2c, 0x20, 0x49,
      0x6e, 0x63, 0x2e, 0x12, 0xc,  0x43, 0x61, 0x72, 0x64, 0x62, 0x6f,
      0x61, 0x72, 0x64, 0x20, 0x76, 0x31, 0x1d, 0x31, 0x8,  0x2c, 0x3d,
      0x25, 0x8f, 0xc2, 0x75, 0x3d, 0x2a, 0x10, 0x0,  0x0,  0x20, 0x42,
      0x0,  0x0,  0x20, 0x42, 0x0,  0x0,  0x20, 0x42, 0x0,  0x0,  0x20,
      0x42, 0x35, 0x29, 0x5c, 0xf,  0x3d, 0x3a, 0x8,  0xc1, 0xca, 0xe1,
      0x3e, 0x77, 0xbe, 0x1f, 0x3e, 0x58, 0x0,  0x60, 0x1,
  };
}

}  // namespace cardboard::qrcode
=======
#include <string>

#include "cardboard_device.pb.h"

namespace cardboard {
namespace qrcode {

// Device params for Cardboard V1 released at Google I/O 2014.
static constexpr float kCardboardV1InterLensDistance = 0.06f;
static constexpr float kCardboardV1TrayToLensDistance = 0.035f;
static constexpr float kCardboardV1VirtualEyeToScreenDistance = 0.042f;
static constexpr float kCardboardV1FovHalfDegrees[] = {40.0f, 40.0f, 40.0f,
                                                       40.0f};
static constexpr float kCardboardV1DistortionCoeffs[] = {0.441f, 0.156f};
static constexpr char kCardboardV1Vendor[] = "Google, Inc.";
static constexpr char kCardboardV1Model[] = "Cardboard v1";

std::vector<uint8_t> getCardboardV1DeviceParams() {
  DeviceParams cardboard_v1_params;
  cardboard_v1_params.set_vendor(kCardboardV1Vendor);
  cardboard_v1_params.set_model(kCardboardV1Model);
  cardboard_v1_params.set_screen_to_lens_distance(
      kCardboardV1VirtualEyeToScreenDistance);
  cardboard_v1_params.set_inter_lens_distance(kCardboardV1InterLensDistance);
  for (float degree : kCardboardV1FovHalfDegrees) {
    cardboard_v1_params.add_left_eye_field_of_view_angles(degree);
  }

  cardboard_v1_params.set_primary_button(DeviceParams_ButtonType_MAGNET);
  cardboard_v1_params.set_vertical_alignment(
      DeviceParams_VerticalAlignmentType_BOTTOM);
  cardboard_v1_params.set_tray_to_lens_distance(kCardboardV1TrayToLensDistance);
  for (float coefficient : kCardboardV1DistortionCoeffs) {
    cardboard_v1_params.add_distortion_coefficients(coefficient);
  }

  std::string serialized_params;
  cardboard_v1_params.SerializeToString(&serialized_params);
  return std::vector<uint8_t>(serialized_params.begin(),
                              serialized_params.end());
}

}  // namespace qrcode
}  // namespace cardboard
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
