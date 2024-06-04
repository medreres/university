require "application_system_test_case"

class PassangersTest < ApplicationSystemTestCase
  setup do
    @passanger = passangers(:one)
  end

  test "visiting the index" do
    visit passangers_url
    assert_selector "h1", text: "Passangers"
  end

  test "should create passanger" do
    visit passangers_url
    click_on "New passanger"

    fill_in "First name", with: @passanger.first_name
    fill_in "Items count", with: @passanger.items_count
    fill_in "Items weight", with: @passanger.items_weight
    fill_in "Last name", with: @passanger.last_name
    click_on "Create Passanger"

    assert_text "Passanger was successfully created"
    click_on "Back"
  end

  test "should update Passanger" do
    visit passanger_url(@passanger)
    click_on "Edit this passanger", match: :first

    fill_in "First name", with: @passanger.first_name
    fill_in "Items count", with: @passanger.items_count
    fill_in "Items weight", with: @passanger.items_weight
    fill_in "Last name", with: @passanger.last_name
    click_on "Update Passanger"

    assert_text "Passanger was successfully updated"
    click_on "Back"
  end

  test "should destroy Passanger" do
    visit passanger_url(@passanger)
    click_on "Destroy this passanger", match: :first

    assert_text "Passanger was successfully destroyed"
  end
end
