// #include <wrappers/ruby/wrapper.hpp>

// Wrappers::Ruby::Wrapper::Wrapper()
// {
//   eBoks_ = rb_define_module("eBoks");

//   VALUE cClient = rb_define_class_under(eBoks_, "Client", rb_cObject);

//   rb_define_method(cClient, "initialize", this->Initialize, 0);
//   rb_define_method(cClient, "set_nation", this->SetNation, 1);
//   rb_define_method(cClient, "set_identity_type", this->SetIdentityType, 1);
//   rb_define_method(cClient, "set_credentials", this->SetCredentials, 3);
//   rb_define_method(cClient, "login", this->Login, 0);
//   rb_define_method(cClient, "fetch_inbox", this->FetchInbox, -1);


// }

// VALUE
// Wrappers::Ruby::Wrapper::Initialize(VALUE self)
// {
//   VALUE user_id = rb_int_new();
//   rb_iv_set(self, "@user_id", user_id);

//   VALUE session_id = rb_int_new();
//   rb_iv_set(self, "@session_id", session_id);

//   VALUE messages = rb_ary_new();
//   rb_iv_set(self, "@messages", messages);
// }

// VALUE
// Wrappers::Ruby::Wrapper::SetCredentials(VALUE self,
//                                         VALUE person_number,
//                                         VALUE passphrase,
//                                         VALUE activation_code)
// {
//   // Validate data types
//   Check_Type(name, T_STRING);
//   FIXNUM_P(person_number);

//   Check_Type(identity_type, T_STRING);
//   if (RSTRING(identity_type)->len != 1) {
//     rb_raise(rb_eTypeError, "identity type must be either 'P' or 'X'");
//   }

//   Check_Type(nationality, T_STRING);
//   if (RSTRING(nationality)->len != 2) {
//     rb_raise(rb_eTypeError,
//              "nationality is defined as two letters e.g. 'DK', 'SE', 'NO'.");
//   }

//   Check_Type(passphrase, T_STRING);
//   Check_Type(activation_code, T_STRING);

//   Identity *identity = new Identity(person_number,
//                                     (RSTRING(identity_type)->ptr)[0]);

//   User *user = new User(name, &identity, passphrase, activation_code);
// }

// VALUE
// Wrappers::Ruby::Wrapper::Connect(VALUE self)
// {

// }

// VALUE
// Wrappers::Ruby::Wrapper::FetchInbox(VALUE self, VALUE obj)
// {

// }
