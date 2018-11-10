# TinyPic
To edit a ppm (P3 and P6) image, simply yet efficiently.

Can be tested with (for example) :

```c++
#include <iostream>
#include "ppm.h"

int main(int argc, char *argv[])
{
	std::cout << "begin test" << std::endl;

	ppm::PPM p;
	p.blueImage();
	p.horizontalLine(100);
	p.verticalLine(50);
	p.saveP6Format("toto.ppm");

	std::cout << "end test" << std::endl;

	return 0;
}
```
Do whatever you want with it.
