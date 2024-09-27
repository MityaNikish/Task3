#pragma once
#include <vector>


struct Layer
{
	//������� ������
	double thickness_ = 0;

	//������������� ������
	double resistance_ = 0;

	//������ ���� ������������� ����������
	double penetration_zone_radius_ = 0;

	//������������� ���� �������������
	double penetration_zone_resistance_ = 0;
};


struct Probe
{
	//���������� ����� ���������� � ��������� ����������
	double distance_between_source_and_receiver_ = 0;

	//���������� ����� ����������
	double distance_between_receivers_ = 0;

	//���� ����
	double amperage_ = 0;

	//����� ��������� k_i ������ ������ 1 <= i <= m
	size_t quantity_measurements_ = 0;

	//���������� ����� �� ������������ ���
	std::vector<double> vertical_coordinates;

	//�������� �����������
	std::vector<double> potential_differences;
};


struct DataBKS
{
	//������ ��������
	double well_radius_ = 0;

	//������������� �������� ��������
	double drilling_mud_resistance_ = 0;

	//������������� �������� ���������� ������
	double upper_enclosing_layer_resistance_ = 0;

	//������������� ������� ���������� ������
	double lower_enclosing_layer_resistance_ = 0;

	//����� �������
	size_t quantity_layers_ = 0;

	//������ �������
	std::vector<Layer> layers_;

	//����� ������
	size_t quantity_probes_ = 0;

	//������ ������
	std::vector<Probe> probes_;

	//��� ������������� �� ������������ ���
	double h_z_;

	//��� ������������� �������������� ���
	double h_r_;

	//������������ ����� �� �������������� ���
	double max_r_;

	//����� ����� ����� ��� ������������� ��������� �����
	size_t quantity_nodes_;
};
