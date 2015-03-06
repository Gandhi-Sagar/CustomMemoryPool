#include <stddef.h>

class CPool
{ 
	unsigned int		m_uiBlocks;		// Num of blocks
	unsigned int		m_uiSizeOfBlock;	// Size of each block
	unsigned int		m_uiFreeBlocks;	// Num of remaining blocks
	unsigned int		m_uiInitialized;	// Num of initialized blocks
	unsigned char	   *m_pMemStart;			// Beginning of memory pool
	unsigned char	   *m_pNext;				// Num of next free block
	
	public:
			CPool();
			~CPool();
			
			void				CreatePool(size_t sizeOfEachBlock,	unsigned int numOfBlocks);
			void				DestroyPool();
	
			unsigned char*		AddrFromIndex(unsigned int i) const;
			unsigned int		IndexFromAddr(const unsigned char* p) const;
			
			void*				Allocate();
			void				DeAllocate(void* p);
};


// With global operators, this new would be `placement new`, but I did not find the easy way to call deallocator.
// one palce was to call destructor explicitely, but it makes system unstable: one way to allocate and other way to deallocate
// Also user had to implement objPool.DeAllocate() in destructor. So finding way around this approach..
/*
inline void* operator new(size_t dead_param, CPool&  objPool)
{
	return objPool.Allocate();
}

inline void operator delete(void* ptr, CPool& objPool)
{
	objPool.DeAllocate(ptr);
}*/

