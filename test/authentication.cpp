// #include "gtest/gtest.h"
// #include "gmock/gmock.h"


// class AuthenticationTest : public testing::Test {
//  protected:
//    *burst_counter_;

//   BurstCounterTest() {
//   }

//   virtual ~BurstCounterTest() {
//   }

//   virtual void SetUp() {

//     burst_counter_ = new GSM::BurstCounter();
//   }

//   virtual void TearDown() {
//     delete burst_counter_;
//   }
// };

// TEST_F(AuthenticationTest, StoreCredentialsInConfiguration) {

// }

// TEST_F(AuthenticationTest, SessionRequestIsGeneratedCorrectly) {
//   std::string name = "John Doe";
//   Identity *identity = new Identity(1234567890, 'P');
//   std::string passphrase = "1a2b3c4d5e";
//   std::string activation_code = "1234AbCd";

//   User *user = new User(name, &identity, passphrase, activation_code);
//   // ASSERT_EQ(GSM::BurstCounter::FREQUENCY_CORRECTION, burst_counter_->GetType());
// }
