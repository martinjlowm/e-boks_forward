require 'minitest/autorun'
require 'eboks'

class TesteBoks < Minitest::Test
  def setup
    @eboks = eBoks::Client.new

    @eboks.set_credentials('John Doe', 1234567890, 'P', 'DK', '1a2b3c4d5e',
                           '1234AbCd')
  end

  def test_that_session_id_is_stored
    @eboks.connect # Mock this
    assert_equal 'd67510fb-c7e0-4951-af09-7c357af928b9', @eboks.session_id
  end

  def test_that_user_id_is_stored
    @eboks.connect # Mock this
    assert_equal '4299841', @eboks.user_id
  end

  def test_that_inbox_response_has_valid_xml_for_ten_messages
    @eboks.connect # Mock this
    @eboks.fetch_inbox(10)
    assert_equal 10, @eboks.messages.length
  end
end
