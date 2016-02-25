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

#include "eboks/application.hpp"

#ifdef _WIN32_
#include <windows.h>
#else
#include <sys/utsname.h>
#ifdef _APPLE_
#include <CoreServices/CoreServices.h>
#else
#include <fstream>
#endif
#endif

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>


// Constructors
eBoks::Application::Application()
    : user_(), logon_(), handler_(this) {
  DetermineDevice();
  device_id_ = kFakeDeviceID;
  DetermineOS();
  version_ = "1.5.0";  // Hardcode version for now.
}

// Accessors and mutators
std::string eBoks::Application::device() const { return device_; }
std::string eBoks::Application::device_id() const { return device_id_; }
void eBoks::Application::DetermineDevice() {
  std::string machine;
#ifdef _WIN32_
  SYSTEM_INFO system_info;

  GetSystemInfo(&system_info);
  machine = system_info.dwProcessorType;
#else
  struct utsname system_info;

  uname(&system_info);
  machine = system_info.machine;
#endif

  device_ = machine;
}

std::string eBoks::Application::os() const { return os_; }
std::string eBoks::Application::os_version() const { return os_version_; }
void eBoks::Application::DetermineOS() {
  std::stringstream version_stream;
#ifdef _WIN32_
  OSVERSIONINFO osvi;
  BOOL bIsWindowsXPorLater;

  ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
  osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

  GetVersionEx(&osvi);

  version_stream << osvi.dwMajorVersion;
  version_stream << ".";
  version_stream << osvi.dwMinorVersion;

  os_ = "Windows";
  os_version_ = version_stream.str();

#elif _APPLE_
  SInt32 major_version, minor_version, bugfix_version;

  Gestalt(gestaltSystemVersionMajor, &major_version);
  Gestalt(gestaltSystemVersionMinor, &minor_version);
  Gestalt(gestaltSystemVersionBugFix, &bugfix_version);

  version_stream << major_version;
  version_stream << ".";
  version_stream << minor_version;
  version_stream << ".";
  version_stream << bugfix_version;

  os_ = "OS X";
  os_version_ = version_stream.str();
#else
  // Support Linux
  // std::ifstream f("/bin/lsb_release");
  // if (f.good()) {

  // }
  // f = "/etc/os-release";
  os_ = "Linux";
  os_version_ = "x.x.x";
#endif
}

std::string eBoks::Application::version() const { return version_; }
void eBoks::Application::set_version(std::string const &version) {
  version_ = version;
}

eBoks::Logon eBoks::Application::logon() const { return logon_; }
eBoks::User eBoks::Application::user() const { return user_; }
eBoks::Connection::Handler eBoks::Application::handler() const { return handler_; }

void eBoks::Application::AddXML(pugi::xml_node parent) {
  pugi::xml_node node = parent.append_child("App");

  node.append_attribute("Device") = device().c_str();
  node.append_attribute("os") = os().c_str();
  node.append_attribute("osVersion") = os_version().c_str();
  node.append_attribute("version") = version().c_str();
}

void eBoks::Application::SetNation(std::string const &nation) {
  try {
    user_.identity().set_nationality(nation);
  } catch (const std::invalid_argument &e) {
    std::cerr << "Invalid argument: " << e.what() << "\n";
  }
}

void eBoks::Application::SetIdentityType(std::string const &type) {
  try {
    user_.identity().set_type(type);
  } catch (const std::invalid_argument &e) {
    std::cerr << "Invalid argument: " << e.what() << "\n";
  }
}

void eBoks::Application::SetCredentials(std::string const &identity_number,
                                        std::string const &passphrase,
                                        std::string const &activation_code) {
  try {
    user_.identity().set_number(identity_number);
  } catch (const std::invalid_argument &e) {
    std::cerr << "Invalid argument: " << e.what() << "\n";
  }

  user_.set_passphrase(passphrase);
  user_.set_activation_code(activation_code);
}
