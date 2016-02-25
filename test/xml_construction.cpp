/*
 * Copyright (c) 2015-2016, Martin Jesper Low Madsen
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

#include <string>

#include "pugixml.hpp"

#include "eboks/application.hpp"
#include "eboks/connection/handler.hpp"
#include "eboks/user.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#ifdef _WIN32_
#include <windows.h>
#else
#include <sys/utsname.h>
#ifdef _APPLE_
#include <CoreServices/CoreServices.h>
#else
#include <fstream>
#endif  // _APPLE_
#endif  // _WIN32_

class XMLConstructionTest : public testing::Test {
 public:
  pugi::xml_document doc_;
  std::stringstream xml_string_;

  std::string machine_;
  std::string os_;
  std::string os_version_;

  XMLConstructionTest() {}

  virtual ~XMLConstructionTest() {}

  virtual void SetUp() {}

  virtual void TearDown() {
    xml_string_.str("");
  }
};

TEST_F(XMLConstructionTest, GenerateValidApplicationXMLString) {
  std::string app_version = "1.5.0";

  eBoks::Application app = eBoks::Application();

  app.AddXML(doc_);
  doc_.print(xml_string_);

  std::stringstream expected_string;
  expected_string << "<App Device=\"";
  expected_string << app.device();
  expected_string << "\" os=\"";
  expected_string << app.os();
  expected_string << "\" osVersion=\"";
  expected_string << app.os_version();
  expected_string << "\" version=\"";
  expected_string << app_version;
  expected_string << "\" />\n";

  ASSERT_EQ(expected_string.str(), xml_string_.str());
}

TEST_F(XMLConstructionTest, GenerateValidUserXMLString) {
  std::string identity_number = "1234567890";
  std::string identity_type = "P";
  std::string nationality = "DK";
  std::string passphrase = "1a2b3c4d5e";
  std::string activation_code = "1234AbCd";

  eBoks::Application app = eBoks::Application();
  app.SetNation(nationality);
  app.SetIdentityType(identity_type);

  app.SetCredentials(identity_number, passphrase, activation_code);

  app.user().AddXML(doc_);
  doc_.print(xml_string_);

  std::stringstream expected_string;
  expected_string << "<User identity=\"1234567890\" ";
  expected_string <<       "identityType=\"P\" ";
  expected_string <<       "nationality=\"DK\" ";
  expected_string <<       "pincode=\"1a2b3c4d5e\" />\n";

  ASSERT_EQ(expected_string.str(), xml_string_.str());
}

TEST_F(XMLConstructionTest, GenerateValidLogonXMLString) {
  std::string identity_type = "P";
  std::string nationality = "DK";
  std::string identity_number = "1234567890";
  std::string passphrase = "1a2b3c4d5e";
  std::string activation_code = "1234AbCd";

  eBoks::Application app = eBoks::Application();
  app.SetNation(nationality);
  app.SetIdentityType(identity_type);

  app.SetCredentials(identity_number, passphrase, activation_code);

  eBoks::Connection::Handler handler = app.handler();
  std::string xml_string = handler.GenerateAuthenticationBody();

  std::stringstream expected_string;
  expected_string << "<Logon xmlns=\"urn:eboks:mobile:1.0.0\" ";
  expected_string <<        "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" ";
  expected_string <<        "xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\">\n";
  expected_string << "	<App Device=\"A0001\" os=\"Android\" ";
  expected_string <<        "osVersion=\"5.1.1\" version=\"1.5.0\" />\n";
  expected_string << "	<User identity=\"1234567890\" identityType=\"P\" ";
  expected_string <<         "nationality=\"DK\" pincode=\"1a2b3c4d5e\" />\n";
  expected_string << "</Logon>\n";

  ASSERT_EQ(expected_string.str(), xml_string);

}
