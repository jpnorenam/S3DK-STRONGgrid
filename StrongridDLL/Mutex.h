/*
*  Mutex.h
*
*  Copyright (C) 2017 Luigi Vanfretti
*
*  This file is part of StrongridDLL.
*
*  StrongridDLL is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  StrongridDLL is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with StrongridDLL.  If not, see <http://www.gnu.org/licenses/>.
*
*/

#pragma once
#ifdef _WIN32
#include <Windows.h>
#else
#include <pthread.h>
#include <math.h>
#endif 


namespace stronggriddll
{
	class Mutex
	{
	public:
		Mutex();
		~Mutex();

		bool Enter( int timeoutMs );
		void Exit();

	private:
#ifdef _WIN32
		HANDLE m_hMutex;
#else
		pthread_mutex_t m_hMutex;
#endif
	};

	class MutexFragment
	{
	public:
		MutexFragment( Mutex* mutex, int timeout = (int)INFINITY )
		{
			m_mutex = mutex;
			m_mutex->Enter(timeout);
		}

		~MutexFragment()
		{
			Finalize();
		}

		void Finalize()
		{
			if( m_mutex ) m_mutex->Exit();
			m_mutex = 0;
		}

	private:
		Mutex* m_mutex;
	};

}
