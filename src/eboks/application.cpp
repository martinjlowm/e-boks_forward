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

#include "eboks/application.hpp"

#include <iostream>
#include <string>


// Constructors
eBoks::Application::Application(std::string device, std::string os,
                                std::string os_version,
                                std::string app_version)
    : device_(device),
      os_(os),
      os_version_(os_version),
      version_(app_version) {}

// Accessors and mutators
std::string eBoks::Application::device() const { return device_; }
void eBoks::Application::set_device(std::string const &device) {
  device_ = device;
}

std::string eBoks::Application::os() const { return os_; }
void eBoks::Application::set_os(std::string const &os) {
  os_ = os;
}

std::string eBoks::Application::os_version() const { return os_version_; }
void eBoks::Application::set_os_version(std::string const &os_version) {
  os_version_ = os_version;
}

std::string eBoks::Application::version() const { return version_; }
void eBoks::Application::set_version(std::string const &version) {
  version_ = version;
}

void eBoks::Application::AddXML(pugi::xml_node parent) {
  pugi::xml_node node = parent.append_child("App");

  node.append_attribute("Device") = device().c_str();
  node.append_attribute("os") = os().c_str();
  node.append_attribute("osVersion") = os_version().c_str();
  node.append_attribute("version") = version().c_str();
}
