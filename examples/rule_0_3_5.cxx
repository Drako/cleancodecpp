// Rule of 0: A class should not have any of destructor/assignment operator/copy constructor

template<typename T>
struct Point final
{
  T x;
  T y;
};

// Rule of 3: A class with a custom destructor SHOULD also have a custom assignment operator AND copy constructor.
// The existence of a custom destructor usually implies some kind of resource management,
// in turn in most cases assignment operator and copy constructor also need to be defined to take care of that.
// Explicitly deleting assignment operator and copy constructor is a valid path here.

template<typename Mtx>
class ScopedLock final
{
  Mtx &_mtx;

public:
  explicit ScopedLock(Mtx &mtx)
    : _mtx{mtx}
  {
    _mtx.lock();
  }

  ~ScopedLock()
  {
    _mtx.unlock();
  }

  ScopedLock(ScopedLock const &) = delete;
  ScopedLock &operator=(ScopedLock const &) = delete;
};

// Rule of 5: A class with a custom destructor SHOULD also have a custom copy-assignment & move-assignment operator AND copy-constructor & move-constructor.
// This is an extension to the old rule of three. While the default move-assignment and move-construction just forward to the respective copies,
// in cases where we have a custom destructor, we usually also want a different move behaviour.
// For types that should be neither copyable nor movable, it suffices to delete the copy-constructor and copy-assignment operator.

#include <utility>

template<typename T>
class UniquePtr final
{
  T *_ptr;

  void release()
  {
    delete _ptr;
  }

public:
  explicit UniquePtr(T *ptr = nullptr)
    : _ptr{ptr}
  {}

  ~UniquePtr()
  {
    release();
  }

  UniquePtr(UniquePtr const &) = delete;
  UniquePtr &operator=(UniquePtr const &) = delete;

  UniquePtr(UniquePtr &&src)
    : _ptr{src._ptr}
  {
    src._ptr = nullptr;
  }

  UniquePtr &operator=(UniquePtr &&src)
  {
    // important: when implementing move-assignment, keep in mind to check for self-assignments
    if (this == std::addressof(src)) {
      return *this;
    }

    release();
    _ptr = src._ptr;
    src._ptr = nullptr;

    return *this;
  }
};
