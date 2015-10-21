require 'minitest/autorun'
require 'eboks'

class TesteBoks < Minitest::Test
  def setup
    @app = eBoks::Application.new
    @app.set_nation('DK')
    @app.set_identity_type('P')
    # Social security number, passphrase, activation code
    @app.set_credentials('1234567890', '1a2b3c4d5e', '1234AbCd')
    # No need to flood the server, thus mock the following call
    @app.login
  end

  def test_that_session_id_is_stored
    assert_equal 'd67510fb-c7e0-4951-af09-7c357af928b9', @app.session_id
  end

  def test_that_user_id_is_stored
    assert_equal '4299841', @app.user_id
  end

  def test_that_inbox_response_has_valid_xml_for_ten_messages
    @app.fetch_inbox(10)
    assert_equal 10, @app.messages.length
  end
end
