#include "discretization.h"
#include <vector>



void discretization(const DataBKS& data)
{
	//Суммарная толщина всех слоев
	double sum_thicknes = 0;
	for (size_t i = 0; i < data.quantity_layers_; ++i )
	{
		sum_thicknes += data.layers_[i].thickness_;
	}

	//Количество узлов по Z
	size_t quontity_nodes_z = sum_thicknes / data.h_z_;

	//Координаты узлов по Z
	std::vector<double> value_z(quontity_nodes_z);
	for (size_t index_z = 0; index_z < quontity_nodes_z; ++index_z)
	{
		value_z[index_z] = static_cast<double>(index_z) * data.h_z_;
	}

	//Количество узлов по R
	size_t quontity_nodes_r = data.max_r_ / data.h_r_;

	//Координаты узлов по R
	std::vector<double> value_r(quontity_nodes_r);
	for (size_t index_r = 0; index_r < quontity_nodes_r; ++index_r)
	{
		value_r[index_r] = static_cast<double>(index_r) * data.h_r_;
	}

	//Значения в узлах - сопротивление
	std::vector<double> medium(quontity_nodes_z * quontity_nodes_r, 0);



	double h[5] = { 0.1, 0.2, 0.3, 0.4, 0.5 };
	double r[5] = { 0.0, 0.0, 0.0, 0.0, 0.0 };
	double p_h[3] = { 0, 0.23, 0.45 };
	double p_r[3] = { 23.5, 12.5, 3.76 };




	//
	for (size_t i = 0; i < data.quantity_layers_; ++i)
	{
		size_t index_p = 0;
		const Layer& layer = data.layers_[i];
		const Probe& probe = data.probes_[i];

		//int step_cell = 0;

		////for (int i = 0; i < 3 - 1; ++i)
		//for (size_t index_z = 0; index_z < quontity_nodes_z; ++index_z)
		//{
		//	for (; (step_cell < probe.vertical_coordinates.size()) && (p_h[i] < h[step_cell] && h[step_cell] < p_h[i + 1]); ++step_cell)
		//	{
		//		r[step_cell] = p_r[i] + (h[step_cell] - p_h[i]) / (p_h[i + 1] - p_h[i]) * (p_r[i + 1] - p_r[i]);
		//	}
		//}

		//for (; step_cell < 5; ++step_cell)
		//{
		//	r[step_cell] = p_r[2];
		//}


		for (size_t index_z = 0; index_z < quontity_nodes_z; ++index_z)
		{
			double moment_resistance = 0;

			//if (probe.vertical_coordinates[index_p] < value_z[index_z])
			//if (index_z == 0)
			//{
			//	moment_resistance = probe.potential_differences[index_p];

			//}


			for (size_t index_r = 0; index_r < quontity_nodes_r; ++index_r)
			{
				if (value_r[index_r] < data.well_radius_)
				{
					medium[index_z * quontity_nodes_r + index_r] = data.drilling_mud_resistance_;
				}
				else if (value_r[index_r] < layer.penetration_zone_radius_)
				{
					medium[index_z * quontity_nodes_r + index_r] = layer.penetration_zone_resistance_;
				}
				else
				{
					//medium[index_z * quontity_nodes_r + index_r] =
				}

			}
		}
	}
}