#include "reader.h"
#include "writer.h"
#include "discretization.h"


int main()
{
	DataBKS exemple;

	reader(exemple);
	writer(exemple);

	discretization(exemple);

	return 0;
}
