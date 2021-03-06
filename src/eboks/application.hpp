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

#ifndef EBOKS_APPLICATION_HPP_
#define EBOKS_APPLICATION_HPP_

#include <string>

#include "eboks/connection/handler.hpp"
#include "eboks/time_manager.hpp"
#include "eboks/user.hpp"
#include "eboks/xml_constructor.hpp"

namespace eBoks {

class Application : public XMLConstructor {
 public:
  Application();

  std::string device() const;
  std::string device_id() const;
  void DetermineDevice();

  std::string os() const;
  std::string os_version() const;
  void DetermineOS();

  std::string version() const;
  void set_version(std::string const &version);

  User user() const;
  Logon logon() const;
  Connection::Handler handler() const;

  void AddXML(pugi::xml_node parent);

  // Configuration
  void SetNation(std::string const &nation);
  void SetIdentityType(std::string const &identity_type);
  void SetCredentials(std::string const &identity_number,
                      std::string const &passphrase,
                      std::string const &activation_code);

  // Actions
  void Connect();

 private:
  std::string device_;  // e.g. A0001 (OnePlus One)
  std::string device_id_;  // e.g. Settings.Secure#ANDROID_ID
  std::string os_;  // e.g. Android
  std::string os_version_;  // e.g. 5.1.1
  std::string version_;  // e.g. e-Boks 1.5.0

  User user_;
  Logon logon_;
  TimeManager time_manager;
  Connection::Handler handler_;
};

}  // namespace eBoks

#endif  // EBOKS_APPLICATION_HPP_
