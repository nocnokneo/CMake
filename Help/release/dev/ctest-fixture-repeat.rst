ctest-fixture-repeat
--------------------

* :manual:`ctest(1)` :option:`--repeat <ctest --repeat>` mode now supports
  different fixture repetition behaviors through the new
  :prop_test:`FIXTURE_REPEAT_MODE` test property. The default behavior is
  controlled by the new :policy:`CMP0210` policy:

  * Policy ``NEW`` (default in CMake 3.32+): ``EACH_REPEAT`` mode runs the
    entire fixture cycle (setup → test → cleanup) for each test repetition.

  * Policy ``OLD``: ``BATCHED_EACH_REPEAT`` mode (legacy behavior) where
    all tests including fixtures are repeated in batches.

  The ``ONCE`` mode can also be explicitly set to run fixtures only once
  around all test repetitions.

  See the :prop_test:`FIXTURE_REPEAT_MODE` property documentation for details.
