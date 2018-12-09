#pragma once

struct Time
{
    int Year;
    unsigned int Month;
    unsigned int Day;
    unsigned int Hour;
    unsigned int Minute;
};

enum class EventType
{
    GuardChange,
    FallAsleep,
    WakeUp
};

typedef unsigned int GuardId;

struct Record
{
    Time TimeStamp;
    EventType Event;
    GuardId Guard;
};

// Generated with the following regex commands
// %s/\[\(\d*\)-\(\d*\)-\(\d*\) \(\d*\):\(\d*\)\] Guard #\(\d*\) begins shift/    { { \1, \2, \3, \4, \5 }, EventType::GuardChange, \6 },
// %s/\[\(\d*\)-\(\d*\)-\(\d*\) \(\d*\):\(\d*\)\] falls asleep/    { { \1, \2, \3, \4, \5 }, EventType::FallAsleep, 0 },
// %s/\[\(\d*\)-\(\d*\)-\(\d*\) \(\d*\):\(\d*\)\] wakes up/    { { \1, \2, \3, \4, \5 }, EventType::WakeUp, 0 },
const std::array<Record, 17> sample_records = { {
    { { 1518, 11, 01, 00, 00 }, EventType::GuardChange, 10 },
    { { 1518, 11, 01, 00, 05 }, EventType::FallAsleep, 0 },
    { { 1518, 11, 01, 00, 25 }, EventType::WakeUp, 0 },
    { { 1518, 11, 01, 00, 30 }, EventType::FallAsleep, 0 },
    { { 1518, 11, 01, 00, 55 }, EventType::WakeUp, 0 },
    { { 1518, 11, 01, 23, 58 }, EventType::GuardChange, 99 },
    { { 1518, 11, 02, 00, 40 }, EventType::FallAsleep, 0 },
    { { 1518, 11, 02, 00, 50 }, EventType::WakeUp, 0 },
    { { 1518, 11, 03, 00, 05 }, EventType::GuardChange, 10 },
    { { 1518, 11, 03, 00, 24 }, EventType::FallAsleep, 0 },
    { { 1518, 11, 03, 00, 29 }, EventType::WakeUp, 0 },
    { { 1518, 11, 04, 00, 02 }, EventType::GuardChange, 99 },
    { { 1518, 11, 04, 00, 36 }, EventType::FallAsleep, 0 },
    { { 1518, 11, 04, 00, 46 }, EventType::WakeUp, 0 },
    { { 1518, 11, 05, 00, 03 }, EventType::GuardChange, 99 },
    { { 1518, 11, 05, 00, 45 }, EventType::FallAsleep, 0 },
    { { 1518, 11, 05, 00, 55 }, EventType::WakeUp, 0 },
} };
