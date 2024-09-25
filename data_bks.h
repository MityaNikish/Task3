#pragma once
#include <vector>


struct Layer
{
	//Толщина пласта
	double thickness_ = 0;

	//Сопротивление пласта
	double resistance_ = 0;

	//Радиус зоны проникновения протекания
	double penetration_zone_radius_ = 0;

	//Сопротивление зоны проникновения
	double penetration_zone_resistance_ = 0;
};


struct Probe
{
	//Расстояние между источником и ближайшим приемником
	double distance_between_source_and_receiver_ = 0;

	//Расстояние между приёмниками
	double distance_between_receivers_ = 0;

	//Сила тока
	double amperage_ = 0;

	//Число измерений k_i данным зондом 1 <= i <= m
	size_t quantity_measurements_ = 0;

	//координаты точек на вертикальной оси
	std::vector<double> vertical_coordinates;

	//разности потенциалов
	std::vector<double> potential_differences;
};


struct DataBKS
{
	//Радиус скважины
	double well_radius_ = 0;

	//Сопротивление бурового раствора
	double drilling_mud_resistance_ = 0;

	//Сопротивление верхнего вмещающего пласта
	double upper_enclosing_layer_resistance_ = 0;

	//Сопротивление нижнего вмещающего пласта
	double lower_enclosing_layer_resistance_ = 0;

	//Число пластов
	size_t quantity_layers_ = 0;

	//Массив пластов
	std::vector<Layer> layers_;

	//Число зондов
	size_t quantity_probes_ = 0;

	//Массив зондов
	std::vector<Probe> probes_;

	//Шаг дискретизации по вертикальной оси
	double h_z_;

	//Шаг дискретизации горизонтальной оси
	double h_r_;

	//Максимальный вынос по горизонтальной оси
	double max_r_;

	//Число узлов сетки для представления вмещающих слоев
	size_t quantity_nodes_;
};
