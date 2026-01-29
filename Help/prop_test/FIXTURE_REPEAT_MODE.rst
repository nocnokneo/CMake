FIXTURE_REPEAT_MODE
-------------------

.. versionadded:: 3.32

Controls how test fixtures behave when tests are repeated using the
:option:`--repeat <ctest --repeat>` option. This property is only meaningful
for tests that have the :prop_test:`FIXTURES_SETUP` or
:prop_test:`FIXTURES_CLEANUP` property set.

The allowed values are:

``ONCE``
  Fixture setup and cleanup tests run only once, while tests that require the
  fixture are repeated. This is the default behavior. The execution order is:
  setup -> test (repeated N times) -> cleanup.

``EACH_REPEAT``
  Runs the entire fixture cycle for each test repetition. The execution order
  is: (setup -> test -> cleanup) repeated N times. This ensures each test
  repetition starts with a fresh fixture setup and proper cleanup.

``BATCHED_EACH_REPEAT``
  Legacy behavior where all tests, including fixture setup and cleanup tests,
  are repeated. The execution order is:
  setup (repeated N times) -> test (repeated N times) -> cleanup (repeated N
  times).

Example:

.. code-block:: cmake

  add_test(NAME setup COMMAND setup_script)
  set_tests_properties(setup PROPERTIES FIXTURES_SETUP MyFixture)

  add_test(NAME mytest COMMAND test_script)
  set_tests_properties(mytest PROPERTIES FIXTURES_REQUIRED MyFixture)

  add_test(NAME cleanup COMMAND cleanup_script)
  set_tests_properties(cleanup PROPERTIES FIXTURES_CLEANUP MyFixture)

With the default ``ONCE`` mode and ``ctest --repeat until-fail:3``:

- ``setup`` runs once
- ``mytest`` runs 3 times
- ``cleanup`` runs once

To run the entire fixture cycle for each repetition:

.. code-block:: cmake

  set_tests_properties(setup cleanup PROPERTIES FIXTURE_REPEAT_MODE EACH_REPEAT)

With ``EACH_REPEAT`` mode and ``ctest --repeat until-fail:3``:

- First cycle: ``setup`` -> ``mytest`` -> ``cleanup``
- Second cycle: ``setup`` -> ``mytest`` -> ``cleanup``
- Third cycle: ``setup`` -> ``mytest`` -> ``cleanup``

See also :prop_test:`FIXTURES_SETUP`, :prop_test:`FIXTURES_CLEANUP`, and
:prop_test:`FIXTURES_REQUIRED`.
