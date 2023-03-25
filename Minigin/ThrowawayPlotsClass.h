#ifndef THROWAWAYPLOTCLASS_H
#define THROWAWAYPLOTCLASS_H
#include "imgui_plot.h"
#include <vector>
#include <memory>
#include "DataCollector.h"

class ThrowawayPlotsClass final
{
public:
	explicit ThrowawayPlotsClass(int arraySize, int defaultSamples);

	void Render();

private:
	std::unique_ptr<DataCollector<int>> m_IntData;
	std::unique_ptr<DataCollector<GameObject3D>> m_GoData;
	std::unique_ptr<DataCollector<GameObject3DAlt>> m_GoAltData;

	std::vector<float> m_IntMeansFloat;
	std::vector<float> m_GOMeansFloat;
	std::vector<float> m_GOAltMeansFloat;

	const float* m_CombinedArray[2];
	ImU32 m_Colors[2]{};


	ImGui::PlotConfig m_IntConfig{};
	ImGui::PlotConfig m_GOConfig{};
	ImGui::PlotConfig m_GOAltConfig{};
	ImGui::PlotConfig m_CombinedConfig{};

	void RunIntDataCollection();
	void RunGO3DDataCollection();
	void RunGO3DALTDataCollection();

	void UpdateConfig(ImGui::PlotConfig& config, const std::vector<float>& values);
};
#endif