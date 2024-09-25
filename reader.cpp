#include "reader.h"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>


void reader(DataBKS& data)
{
	//������� ���� medium.txt
	{
		std::ifstream fin_medium("data\\medium.txt");
		fin_medium >> data.well_radius_;
		fin_medium >> data.drilling_mud_resistance_;
		fin_medium >> data.upper_enclosing_layer_resistance_;
		fin_medium >> data.lower_enclosing_layer_resistance_;
		fin_medium >> data.quantity_layers_;

		//��-��-�� �������, operator>>() ��������� ����� ���� '\n', ������� std::getline() ��������� ��� ��������� ������ ������, ��-�� ���� ����������� ������ ""
		fin_medium.get();

		std::string str;
		for (size_t quantity_layers = 0; quantity_layers < data.quantity_layers_ && std::getline(fin_medium, str); ++quantity_layers)
		{
			Layer layer;
			std::stringstream sstr(str);

			//int arr[4] = { 0 };
			//for (int i = 0; i < 4 && sstr >> arr[i]; ++i)
			//	
			//layer.thickness_ = arr[0];
			//layer.resistance_ = arr[1];
			//layer.penetration_zone_radius_ = arr[2];
			//layer.penetration_zone_resistance_ = arr[3];

			sstr >> layer.thickness_;
			sstr >> layer.resistance_;
			sstr >> layer.penetration_zone_radius_;
			sstr >> layer.penetration_zone_resistance_;

			data.layers_.push_back(layer);
		}

		fin_medium.close();
	}

	//������� ���� probes.txt
	{
		std::ifstream fin_probes("data\\probes.txt");

		fin_probes >> data.quantity_probes_;

		for (size_t quantity_probes = 0; quantity_probes < data.quantity_probes_; ++quantity_probes)
		{
			Probe probe;

			fin_probes >> probe.distance_between_source_and_receiver_;
			fin_probes >> probe.distance_between_receivers_;
			fin_probes >> probe.amperage_;
			fin_probes >> probe.quantity_measurements_;

			data.probes_.push_back(probe);
		}

		fin_probes.close();
	}

	//������� ����� probes_{i}.txt � probes_data_{i}.txt
	{
		for (size_t number_probe = 0; number_probe < data.quantity_probes_; ++number_probe)
		{
			double pos;
			Probe &probe = data.probes_[number_probe];

			std::ifstream fin_vc("data\\probe_" + std::to_string(number_probe + 1) + ".txt");
			for (size_t k = 0; k < probe.quantity_measurements_ && fin_vc >> pos; ++k)
			{
				probe.vertical_coordinates.push_back(pos);
			}
			fin_vc.close();

			std::ifstream fin_pd("data\\probe_data_" + std::to_string(number_probe + 1) + ".txt");

			for (size_t k = 0; k < probe.quantity_measurements_ && fin_pd >> pos; ++k)
			{
				probe.potential_differences.push_back(pos);
			}
			fin_pd.close();
		}
	}
}
 