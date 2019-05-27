/*
Timer
Implement a timer class that implements the interface ITimer which is defined below.
Follow this specification:
Timer allows to determine if specific period of time expired or not since Start was called last time
Timer allows to determine how much time left till period is expired
Timer can be started again any time, no metter in what state it is
*/

/*
 * Architecture:
 * Timer gets interface ITime with such functionality:
 *   get current time point
 * Timer gets desired duration and compares it with current time from ITime
 *
 * Desired behavior:
 * IsExpired returns true if is not started
 * Timeleft returns 0 if is not started or expired
 *
 * Steps:
 * Implement Start with no check
 * Check IsExpired when is not started
 * Check IsExpired when duration is 0 and started
 * Check IsExpired when duration is not 0 and started
 * Check TimeLeft when not started (expected: 0)
 * Check TimeLeft within the given duration and timer is started
 * Check IsExpired within the given duration and timer is started:
 *  immediatly
 *  after some waiting
 * Check TimeLeft when is expired (expected: 0)
 * Check IsExpired when no time left
 * Check IsExpired when time is left
 * Check the starting of timer when it is already started
*/

#include <gtest/gtest.h>
#include <chrono>
