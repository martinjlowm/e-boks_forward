/*
 * Copyright (c) 2015, Martin Jesper Low Madsen
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     *  Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *
 *     *  Redistributions in binary form must reproduce the above copyright
 *        notice, this list of conditions and the following disclaimer in the
 *        documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdexcept>
#include <string>

#include "eboks/user.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

class ExceptionsTest : public testing::Test {
 public:
  eBoks::Identity identity;

  std::string identity_number_;
  std::string identity_type_;
  std::string nationality_;
  std::string passphrase_;
  std::string activation_code_;

  ExceptionsTest() {}

  virtual ~ExceptionsTest() {}

  virtual void SetUp() {
    identity_number_ = "1234567890";
    identity_type_ = "P";
    nationality_ = "DK";

    identity = eBoks::Identity(identity_number_, identity_type_, nationality_);
  }

  virtual void TearDown() {

  }
};

TEST_F(ExceptionsTest, InvalidIdentityType) {
  ASSERT_THROW({
      identity.set_type("A");
    }, std::invalid_argument);
}

TEST_F(ExceptionsTest, ValidIdentityType) {
  ASSERT_NO_THROW({
      identity.set_type("P");
    });
}


TEST_F(ExceptionsTest, InvalidIdentityNumbers) {
  ASSERT_THROW({
      identity.set_number("12345678900");
    }, std::invalid_argument);

  ASSERT_THROW({
      identity.set_number("a234567890");
    }, std::invalid_argument);
}

TEST_F(ExceptionsTest, ValidIdentityNumber) {
  ASSERT_NO_THROW({
    identity.set_number("1234567890");
    });
}


TEST_F(ExceptionsTest, InvalidNationality) {
  ASSERT_THROW({
      identity.set_nationality("DAN");
    }, std::invalid_argument);
}

TEST_F(ExceptionsTest, ValidNationality) {
  ASSERT_NO_THROW({
      identity.set_nationality("DK");
    });
}
