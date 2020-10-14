// Teledyne Marine

// Use and Disclosure of Data
//
// EU Uncontrolled Technology: Information contained herein is uncontrolled
// under the E.U. Regulation (EC) No 428/2009.
// However, export, reexport or diversion contrary to law is prohibited.


#include "stdafx.h"

#include <cstdlib>

#include "Example7k.h"


int main()
{
	if (!NetworkSocket::Init())
		return EXIT_FAILURE;

	Example7k example;
	example.Run("127.0.0.1");

	NetworkSocket::Exit();

	return EXIT_SUCCESS;
}
