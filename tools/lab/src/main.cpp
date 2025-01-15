/* STL inclusions. */
#include <cstdint>
#include <iostream>

/* Local inclusions. */
#include "Libraries/Math/Vector.hpp"

using namespace Libraries::Math;

int
main (int argc, char * * argv)
{
	std::cout << "Lab up ..." "\n";

	const Vector3F absForward{0.0F,  0.0F, -1.0F};
	const Vector3F absUpward{ 0.0F, -1.0F,  0.0F};
	const Vector3F absRight{  1.0F,  0.0F,  0.0F};

	{
		Vector3F upward = Vector3F::crossProduct(absForward, absUpward);

		std::cout << "Upward : " << upward << "\n";
	}

	return EXIT_SUCCESS;
}
