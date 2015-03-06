#include "Pool.h"
#include "TestCases.h"

#include <iostream>
#include <time.h>

const int g_MaxNumberOfObjectsInPool = 1024;

// A small benchmarking code
#ifdef WIN32
#include <windows.h>
double get_time()
{
	LARGE_INTEGER t, f;
	QueryPerformanceCounter(&t);
	QueryPerformanceFrequency(&f);
	return (double)t.QuadPart / (double)f.QuadPart;
}

#else
#include <sys/time.h>
#include <sys/resources.h>

double get_time()
{
	struct timeval t;
	struct timezone tz;
	gettimeofday(&t, &tz);
	return t.tv_sec + t.tv_usec * 1e6;
}
#endif

int main()
{
	double startTime = 0.0;

	// As many Types are there, create those many pools
	CPool	oByteTypePool, oPointerTypePool, oFixedStringTypePool;
	CPool	oPointPool;
	CPool	oBase1Pool, oBase2Pool, oDerivedPool;
	CPool	oNoDefaultCtorPool;

	// create pool for each type

	// for objects whose size is less than 4 bytes, we need additional 4 bytes to do bookkeeping on server side
	oByteTypePool.CreatePool(sizeof(ByteType), g_MaxNumberOfObjectsInPool + 4);					// 0th pool
	oPointerTypePool.CreatePool(sizeof(PointerType), g_MaxNumberOfObjectsInPool);			// 1st pool
	oFixedStringTypePool.CreatePool(sizeof(FixedStringType), g_MaxNumberOfObjectsInPool);	//.. and so on

	oPointPool.CreatePool(sizeof(Point), g_MaxNumberOfObjectsInPool);

	oBase1Pool.CreatePool(sizeof(Base1), g_MaxNumberOfObjectsInPool);
	oBase2Pool.CreatePool(sizeof(Base2), g_MaxNumberOfObjectsInPool);
	oDerivedPool.CreatePool(sizeof(Derived), g_MaxNumberOfObjectsInPool);

	oNoDefaultCtorPool.CreatePool(sizeof(NoDefaultConstructor), g_MaxNumberOfObjectsInPool);// 7th pool

	// randomly select pool to test
	srand((unsigned int)time(NULL));
	int selectedPool = rand() % 8;
	switch(7)
	{
		case 0:
				{
					ByteType	*objBT[g_MaxNumberOfObjectsInPool];

					startTime = get_time();
					for(int i  = 0 ; i < g_MaxNumberOfObjectsInPool ; i++)
					{
						objBT[i] = (ByteType*) oByteTypePool.Allocate();
						// do something with object here
					}

					std::cout << "Allocating "<< g_MaxNumberOfObjectsInPool << " ByteType Objects took " << get_time() - startTime << " seconds" << std::endl;

					// do something with all the objects here, 

					startTime = get_time();
					for(int i  = 0 ; i < g_MaxNumberOfObjectsInPool ; i++)
					{
						oByteTypePool.DeAllocate(objBT[i]);
					}
					std::cout << "DeAllocating "<< g_MaxNumberOfObjectsInPool << " ByteType Objects took " << get_time() - startTime << " seconds" << std::endl;
					break;
				}
		case 1:
				{
					PointerType	*objPT[g_MaxNumberOfObjectsInPool];
					startTime = get_time();
					for(int i  = 0 ; i < g_MaxNumberOfObjectsInPool ; i++)
					{
						objPT[i] = (PointerType*) oPointerTypePool.Allocate();
					}
					std::cout << "Allocating "<< g_MaxNumberOfObjectsInPool << " PointerType Objects took " << get_time() - startTime << " seconds" << std::endl;

					startTime = get_time();
					for(int i  = 0 ; i < g_MaxNumberOfObjectsInPool ; i++)
					{
						oPointerTypePool.DeAllocate(objPT[i]);
					}
					std::cout << "DeAllocating "<< g_MaxNumberOfObjectsInPool << " PointerType Objects took " << get_time() - startTime << " seconds" << std::endl;
					break;
				}

		case 2:
				{
					FixedStringType	*objFST[g_MaxNumberOfObjectsInPool];
					
					startTime = get_time();
					for(int i  = 0 ; i < g_MaxNumberOfObjectsInPool ; i++)
					{
						objFST[i] = (FixedStringType*) oFixedStringTypePool.Allocate();
					}
					std::cout << "Allocating "<< g_MaxNumberOfObjectsInPool << " FixedStringType Objects took " << get_time() - startTime << " seconds" << std::endl;

					startTime = get_time();
					for(int i  = 0 ; i < g_MaxNumberOfObjectsInPool ; i++)
					{
						oFixedStringTypePool.DeAllocate(objFST[i]);
					}
					std::cout << "DeAllocating "<< g_MaxNumberOfObjectsInPool << " FixedStringType Objects took " << get_time() - startTime << " seconds" << std::endl;

					break;
				}

		case 3:
				{
					Point	*objPt[g_MaxNumberOfObjectsInPool];
					
					startTime = get_time();
					for(int i  = 0 ; i < g_MaxNumberOfObjectsInPool ; i++)
					{
						objPt[i] = (Point*) oPointPool.Allocate();
					}
					std::cout << "Allocating "<< g_MaxNumberOfObjectsInPool << " Point Objects took " << get_time() - startTime << " seconds" << std::endl;
			
					startTime = get_time();
					for(int i  = 0 ; i < g_MaxNumberOfObjectsInPool ; i++)
					{
						oPointPool.DeAllocate(objPt[i]);
					}
					std::cout << "DeAllocating "<< g_MaxNumberOfObjectsInPool << " Point Objects took " << get_time() - startTime << " seconds" << std::endl;

					break;
				}

		case 4:
				{
					Base1	*objBase1[g_MaxNumberOfObjectsInPool];

					startTime = get_time();
					for(int i  = 0 ; i < g_MaxNumberOfObjectsInPool ; i++)
					{
						objBase1[i] = (Base1*) oBase1Pool.Allocate();
					}
					std::cout << "Allocating "<< g_MaxNumberOfObjectsInPool << " Base1 Objects took " << get_time() - startTime << " seconds" << std::endl;

					startTime = get_time();
					for(int i  = 0 ; i < g_MaxNumberOfObjectsInPool ; i++)
					{
						oBase1Pool.DeAllocate(objBase1[i]);
					}
					std::cout << "DeAllocating "<< g_MaxNumberOfObjectsInPool << " Base1 Objects took " << get_time() - startTime << " seconds" << std::endl;

					break;
				}
				
		case 5:
				{
					Base2	*objBase2[g_MaxNumberOfObjectsInPool];

					startTime = get_time();
					for(int i  = 0 ; i < g_MaxNumberOfObjectsInPool ; i++)
					{
						objBase2[i] = (Base2*) oBase2Pool.Allocate();
					}
					std::cout << "Allocating "<< g_MaxNumberOfObjectsInPool << " Base2 Objects took " << get_time() - startTime << " seconds" << std::endl;
			
					for(int i  = 0 ; i < g_MaxNumberOfObjectsInPool ; i++)
					{
						oBase2Pool.DeAllocate(objBase2[i]);
					}
					std::cout << "DeAllocating "<< g_MaxNumberOfObjectsInPool << " Base2 Objects took " << get_time() - startTime << " seconds" << std::endl;

					break;
				}
				
		case 6:
				{
					Derived	*objDer[g_MaxNumberOfObjectsInPool];

					startTime = get_time();
					for(int i  = 0 ; i < g_MaxNumberOfObjectsInPool ; i++)
					{
						objDer[i] = (Derived*) oDerivedPool.Allocate();
					}
					std::cout << "Allocating "<< g_MaxNumberOfObjectsInPool << " Derived Objects took " << get_time() - startTime << " seconds" << std::endl;
	
					startTime = get_time();
					for(int i  = 0 ; i < g_MaxNumberOfObjectsInPool ; i++)
					{
						oDerivedPool.DeAllocate(objDer[i]);
					}
					std::cout << "DeAllocating "<< g_MaxNumberOfObjectsInPool << " Derived Objects took " << get_time() - startTime << " seconds" << std::endl;

					break;
				}

		case 7:
				{
					NoDefaultConstructor	*objNDC[g_MaxNumberOfObjectsInPool];
					
					startTime = get_time();
					for(int i  = 0 ; i < g_MaxNumberOfObjectsInPool ; i++)
					{
						objNDC[i] = (NoDefaultConstructor*) oNoDefaultCtorPool.Allocate();
					}
					std::cout << "Allocating "<< g_MaxNumberOfObjectsInPool << " Derived Objects took " << get_time() - startTime << " seconds" << std::endl;
	
					startTime = get_time();
					for(int i  = 0 ; i < g_MaxNumberOfObjectsInPool ; i++)
					{
						oNoDefaultCtorPool.DeAllocate(objNDC[i]);
					}
					std::cout << "DeAllocating "<< g_MaxNumberOfObjectsInPool << " Derived Objects took " << get_time() - startTime << " seconds" << std::endl;

					break;
				}
	}

	// A brave statement: its OKAY if we do not call DestroyPool for all pool objects, in this case
	// Reason --> We are anyway gonna end out process, and after that all resources will be released automatically
	// Just because this is good etiquete of doing programming, I beleive one should not fall for methods. In this particular case
	// while destroying memory may well be on swap space(file in case of windows), and will be brought in just to be freed
	// reference: I am not the only one saying this: http://blogs.msdn.com/b/oldnewthing/archive/2012/01/05/10253268.aspx

	oByteTypePool.DestroyPool();
	oPointerTypePool.DestroyPool();
	oFixedStringTypePool.DestroyPool();

	oPointPool.DestroyPool();

	oBase1Pool.DestroyPool();
	oBase2Pool.DestroyPool();
	oDerivedPool.DestroyPool();

	oNoDefaultCtorPool.DestroyPool();

	return 0;

}
