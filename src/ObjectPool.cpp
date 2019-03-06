#pragma once

#include "ofMain.h"

template<class T, class Initializer, class Activator, class Deactivator> class ObjectPool {
 public:
  using ptr = std::unique_ptr<T, std::function<void(T*)>>;

  ObjectPool(int maxSize = 100, Initializer* init = nullptr)
    : mMaxSize(maxSize), mInitializer(init), mNumActiveObjects(0) {
  }

  void init(int initSize) {
    initSize = std::min(initSize, mMaxSize);
    mPool.resize(initSize);
    initializeRange(0, initSize);
  }

  ptr acquire() {
    if (mFreeIndices.size() == 0) {
      expand();

      if (mFreeIndices.size() == 0) {
        return nullptr;
      }
    }

    int index = *mFreeIndices.begin();
    mFreeIndices.erase(index);
    mNumActiveObjects += 1;

    mActivator(&mPool[index]);
    return ptr(&mPool[index], [this, index](T* elem)->void{ release(elem, index); });
  }

  void getActiveObjects(std::vector<T*>& objects) {
    objects.resize(mNumActiveObjects);

    int j = 0;

    for (int i = 0; i < mPool.size(); ++i) {
      if (mFreeIndices.find(i) == mFreeIndices.end()) {
        objects[j] = &mPool[i];
        j += 1;
      }
    }

    if (j != mNumActiveObjects) {
      ofLog(OF_LOG_ERROR) << "Found " << j << " active objects but expected " << mNumActiveObjects << endl;
    }
  }

 private:
  const float GROWTH_FACTOR = 1.5f;

  int mMaxSize;
  int mNumActiveObjects;

  Initializer* mInitializer;
  Activator mActivator;
  Deactivator mDeactivator;
  std::vector<T> mPool;
  std::set<int> mFreeIndices;

  void initializeRange(int begin, int end) {
    ofLog(OF_LOG_NOTICE) << "Allocating objects to pool from " << begin << " to " << end << endl;

    for (int i = begin; i < end; ++i) {
      if (mInitializer) {
        (*mInitializer)(&mPool[i]);
        mFreeIndices.insert(i);
      } else {
        ofLog(OF_LOG_ERROR) << "The initializer functor cannot be null" << endl;
        break;
      }
    }
  }

  void expand() {
    int initialSize = mPool.size();
    int expandAmount = (int)(mPool.size() * GROWTH_FACTOR);
    int newSize = expandAmount + mPool.size();
    newSize = std::min(newSize, mMaxSize);

    if (newSize > initialSize) {
      mPool.resize(newSize);
      initializeRange(initialSize, newSize);
    }
  }

  void release(T* o, int index) {
    mFreeIndices.insert(index);
    mNumActiveObjects -= 1;
    mDeactivator(o);
  }

};
