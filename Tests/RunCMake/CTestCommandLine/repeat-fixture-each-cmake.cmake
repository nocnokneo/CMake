enable_testing()

# Fixture setup - with EACH_REPEAT mode
add_test(NAME fixture_setup
  COMMAND ${CMAKE_COMMAND} -E echo "fixture_setup")
set_tests_properties(fixture_setup PROPERTIES 
  FIXTURES_SETUP MyFixture
  FIXTURE_REPEAT_MODE EACH_REPEAT)

# Fixture cleanup - with EACH_REPEAT mode
add_test(NAME fixture_cleanup
  COMMAND ${CMAKE_COMMAND} -E echo "fixture_cleanup")
set_tests_properties(fixture_cleanup PROPERTIES 
  FIXTURES_CLEANUP MyFixture
  FIXTURE_REPEAT_MODE EACH_REPEAT)

# Test requiring the fixture
add_test(NAME test_with_fixture
  COMMAND ${CMAKE_COMMAND} -E echo "test_with_fixture")
set_tests_properties(test_with_fixture PROPERTIES FIXTURES_REQUIRED MyFixture)
