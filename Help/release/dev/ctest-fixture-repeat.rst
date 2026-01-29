ctest-fixture-repeat
--------------------

* :manual:`ctest(1)` :option:`--repeat <ctest --repeat>` mode now runs
  fixture setup and cleanup tests only once by default, while repeating only
  the tests that require the fixture. The new :prop_test:`FIXTURE_REPEAT_MODE`
  property can be set on fixture setup and cleanup tests to control this
  behavior. See the :prop_test:`FIXTURES_REQUIRED` property documentation
  for details.
