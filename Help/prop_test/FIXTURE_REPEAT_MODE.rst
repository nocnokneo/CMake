FIXTURE_REPEAT_MODE
-------------------

.. versionadded:: 3.32

Controls how test fixtures behave when tests are repeated using the
:option:`--repeat <ctest --repeat>` option. This property is only meaningful
for tests that have the :prop_test:`FIXTURES_SETUP` or
:prop_test:`FIXTURES_CLEANUP` property set.

If this property is not set on a fixture test, the default value is determined
by the :policy:`CMP0210` policy:

* Policy ``NEW``: Default is ``EACH_REPEAT``
* Policy ``OLD``: Default is ``BATCHED_EACH_REPEAT``

The allowed values are:

``ONCE``
  Fixture setup and cleanup tests run only once, while tests that require the
  fixture are repeated. The execution order is:
  setup -> test (repeated N times) -> cleanup.

``EACH_REPEAT``
  Runs the entire fixture cycle for each test repetition. The execution order
  is: (setup -> test -> cleanup) repeated N times. This ensures each test
  repetition starts with a fresh fixture setup and proper cleanup.

  .. note::

    For ``EACH_REPEAT`` mode to work correctly, **both** the setup and cleanup
    tests for a fixture should have their ``FIXTURE_REPEAT_MODE`` set to
    ``EACH_REPEAT``. The re-queuing of the fixture cycle is triggered when the
    cleanup test completes.

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

With ``EACH_REPEAT`` mode (default with policy CMP0210 NEW) and
``ctest --repeat until-fail:3``:

- First cycle: ``setup`` -> ``mytest`` -> ``cleanup``
- Second cycle: ``setup`` -> ``mytest`` -> ``cleanup``
- Third cycle: ``setup`` -> ``mytest`` -> ``cleanup``

To explicitly set the mode:

.. code-block:: cmake

  set_tests_properties(setup cleanup PROPERTIES FIXTURE_REPEAT_MODE EACH_REPEAT)

See also :prop_test:`FIXTURES_SETUP`, :prop_test:`FIXTURES_CLEANUP`,
:prop_test:`FIXTURES_REQUIRED`, and :policy:`CMP0210`.
