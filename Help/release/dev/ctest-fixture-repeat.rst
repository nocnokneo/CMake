ctest-fixture-repeat
--------------------

* :manual:`ctest(1)` :option:`--repeat <ctest --repeat>` mode now runs
  fixture setup and cleanup tests only once, while repeating only the
  tests that require the fixture. This avoids redundant setup and cleanup
  operations when tests are repeated. See the
  :prop_test:`FIXTURES_REQUIRED` property documentation for details.
