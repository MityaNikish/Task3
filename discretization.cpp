#include "discretization.h"
#include <vector>
#include <fstream>

namespace
{
	//Внесение в сетку вмещающие пласты
	void applicationEnclosingLayers(const EnclosingLayer& enclosing_layers, const size_t quantity_nodes_r, std::vector<double>& medium)
	{
		for (size_t index = 0; index < enclosing_layers.quantity_nodes_ * quantity_nodes_r; ++index)
		{
			medium[index] = enclosing_layers.upper_enclosing_layer_resistance_;
			medium[(medium.size() - 1) - index] = enclosing_layers.lower_enclosing_layer_resistance_;
		}
	}

	//Внесение в сетку пласт
	void applicationLayer(const Layer& layer, const size_t index_z_begin, const size_t index_z_end, std::vector<double>& medium, const std::vector<double>& value_r)
	{
		const size_t quantity_nodes_r = value_r.size();
		for (size_t index_z = index_z_begin; index_z < index_z_end; ++index_z)
		{
			for (size_t index_r = 0; index_r < quantity_nodes_r; ++index_r)
			{
				if (value_r[index_r] < layer.penetration_zone_radius_)
				{
					medium[index_z * quantity_nodes_r + index_r] = layer.penetration_zone_resistance_;
				}
				else
				{
					medium[index_z * quantity_nodes_r + index_r] = layer.resistance_;
				}
			}
		}
	}

	//Внесение в сетку скважину
	void applicationWell(const DataBKS& data, const size_t quantity_nodes_z, std::vector<double>& medium, const std::vector<double>& value_r)
	{
		const size_t quantity_nodes_r = value_r.size();

		for (size_t index_z = 0; index_z < quantity_nodes_z + 2 * data.enclosing_layers_.quantity_nodes_; ++index_z)
		{
			for (size_t index_r = 0; index_r < quantity_nodes_r; ++index_r)
			{
				if (value_r[index_r] >= data.well_radius_)
				{
					break;
				}
				medium[index_z * quantity_nodes_r + index_r] = data.drilling_mud_resistance_;
			}
		}
	}

	//Сохранение дискретизированной среды в бинарном виде
	void saveMedium(std::vector<double>& medium)
	{
		std::ofstream fout("treatment\\medium.raw", std::ios::binary | std::ios::trunc);
		fout.write((char*)medium.data(), sizeof(double) * medium.size());
		fout.close();
	}
}


void discretization(const DataBKS& data)
{
	//Количество узлов по Z
	size_t quantity_nodes_z = 0;
	for (size_t i = 0; i < data.quantity_layers_; ++i )
	{
		quantity_nodes_z += static_cast<size_t>(data.layers_[i].thickness_ / data.h_z_);
	}

	//Координаты узлов по Z
	std::vector<double> value_z(quantity_nodes_z);
	for (size_t index_z = 0; index_z < quantity_nodes_z; ++index_z)
	{
		value_z[index_z] = static_cast<double>(index_z) * data.h_z_;
	}

	//Количество узлов по R
	size_t quantity_nodes_r = static_cast<size_t>(data.max_r_ / data.h_r_);

	//Координаты узлов по R
	std::vector<double> value_r(quantity_nodes_r);
	for (size_t index_r = 0; index_r < quantity_nodes_r; ++index_r)
	{
		value_r[index_r] = static_cast<double>(index_r) * data.h_r_;
	}

	//Значения в узлах - сопротивление
	std::vector<double> medium((quantity_nodes_z + 2 * data.enclosing_layers_.quantity_nodes_) * quantity_nodes_r, 0);

	//Внесение в сетку вмещающие пласты
	applicationEnclosingLayers(data.enclosing_layers_, quantity_nodes_r, medium);

	//Внесение в сетку пласты
	size_t index_z_begin = data.enclosing_layers_.quantity_nodes_;
	for (size_t i = 0; i < data.quantity_layers_; ++i)
	{
		const Layer& layer = data.layers_[i];
		size_t quantity_nodes_z_layer_i = static_cast<size_t>(layer.thickness_ / data.h_z_);
		applicationLayer(layer, index_z_begin, index_z_begin + quantity_nodes_z_layer_i, medium, value_r);
		index_z_begin += quantity_nodes_z_layer_i;
	}

	//Внесение в сетку скважину
	applicationWell(data, quantity_nodes_z, medium, value_r);

	//Сохранение дискретизированной среды в бинарном виде
	saveMedium(medium);
}