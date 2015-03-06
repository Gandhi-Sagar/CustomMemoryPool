#include "Pool.h"

CPool::CPool()
{
	m_uiBlocks = 0;
	m_uiSizeOfBlock = 0;
	m_uiFreeBlocks = 0;
	m_uiInitialized = 0;
	m_pMemStart = NULL;
	m_pNext = 0;
}

CPool::~CPool()
{
	DestroyPool();
}
	
void CPool::CreatePool(size_t sizeOfEachBlock,	unsigned int numOfBlocks)
{
	m_uiBlocks = numOfBlocks;
	m_uiSizeOfBlock = sizeOfEachBlock;
	m_pMemStart = new unsigned char[m_uiSizeOfBlock * m_uiBlocks]; // this allocates contiguous memory, other statements are for bookkeeping only
	m_uiFreeBlocks = numOfBlocks;
	m_pNext = m_pMemStart;
}
	
void CPool::DestroyPool()
{
	delete[] m_pMemStart; // with assumption that you indicated, I hope no one calls this function without first calling CreatePool();
	m_pMemStart = NULL;
}
	
unsigned char* CPool::AddrFromIndex(unsigned int i) const
{
	return m_pMemStart + (i * m_uiSizeOfBlock);
}
	
unsigned int CPool::IndexFromAddr(const unsigned char* p) const
{
	return (((unsigned int)(p - m_pMemStart)) / m_uiSizeOfBlock);
}
	
void* CPool::Allocate()
{
	// Increment no_of_blocks and index
	if (m_uiInitialized < m_uiBlocks)
	{
		unsigned int* p = (unsigned int*)AddrFromIndex(m_uiInitialized);
		*p = m_uiInitialized + 1;
		m_uiInitialized++;
	}
	
	// return one of the free vlock
	void* ret = NULL;
	if (m_uiFreeBlocks > 0)
	{
		ret = (void*)m_pNext;
		--m_uiFreeBlocks;

		if (m_uiFreeBlocks != 0)
		{
			m_pNext = AddrFromIndex(*((unsigned int*)m_pNext));
		}
		else
		{
			m_pNext = NULL;
		}
	}
	return ret;
}
			
void CPool::DeAllocate(void* p)
{
	// its so obvious.. 
	if (m_pNext != NULL)
	{
		(*(unsigned int*)p) = IndexFromAddr(m_pNext);
		m_pNext = (unsigned char*)p;
	}
	else
	{
		*((unsigned int*)p) = m_uiBlocks;
		m_pNext = (unsigned char*)p;
	}
				
	++m_uiFreeBlocks;
}

