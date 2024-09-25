#include "writer.h"
#include <string>
#include <vector>
#include <fstream>


void writer(const DataBKS& data)
{
	for (size_t index_probe = 0; index_probe < data.quantity_probes_; ++index_probe)
	{
		const Probe& probe = data.probes_[index_probe];
		std::vector<double> arr;
		std::ofstream fout("treatment\\probe_" + std::to_string(index_probe + 1) + ".raw", std::ios::binary | std::ios::trunc);

		for (size_t index_measurement = 0; index_measurement < probe.quantity_measurements_; ++index_measurement)
		{
			arr.push_back(probe.vertical_coordinates[index_measurement]);
			arr.push_back(probe.potential_differences[index_measurement]);
		}

		fout.write((char*)arr.data(), sizeof(double) * probe.quantity_measurements_ * 2);
		fout.close();
	}
}
