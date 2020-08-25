/*
*  Mutex.cpp
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

#include "Mutex.h"

using namespace stronggriddll;

Mutex::Mutex()
{
#ifdef  _WIN32
	m_hMutex = CreateMutex(
		NULL,              // default security attributes
		FALSE,             // initially not owned
		NULL);             // unnamed mutex
#else
	pthread_mutex_init(&m_hMutex, NULL);
#endif
}

Mutex::~Mutex()
{
#ifdef  _WIN32
	CloseHandle(m_hMutex);
#else
	pthread_mutex_destroy(&m_hMutex);
#endif
}

bool Mutex::Enter( int timeoutMs )
{
#ifdef  _WIN32
	int result = WaitForSingleObject( m_hMutex, timeoutMs );
	return result == WAIT_OBJECT_0;
#else
	struct timespec timeout;
	timeout.tv_nsec = timeoutMs * 1000000;
	int result = pthread_mutex_timedlock(&m_hMutex, &timeout);
	return result == 0;
#endif
}

void Mutex::Exit()
{
#ifdef  _WIN32
	ReleaseMutex(m_hMutex);
#else
	pthread_mutex_unlock(&m_hMutex);
#endif
}
