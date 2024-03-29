#ifndef CHLLANGE_LOCK_STUB_SYNC_HPP_
#define CHLLANGE_LOCK_STUB_SYNC_HPP_

#include <Challenge/Lock/SyncObject.hpp>

namespace Challenge {

// A class that has a stub implementation of SyncObject
class StubSync final : public SyncObject<StubSync>
{
public:
    void enter() { /* stub */ }
    void leave() { /* stub */ }
};

}; // namespace Challenge

#endif // CHLLANGE_LOCK_STUB_SYNC_HPP_
