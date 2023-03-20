#include "ThrowawayPlotsClass.h"

ThrowawayPlotsClass::ThrowawayPlotsClass(int arraySize, int defaultSamples)
{
	m_IntData = std::make_unique<DataCollector<int>>(arraySize, defaultSamples);
	m_GoData = std::make_unique<DataCollector<GameObject3D>>(arraySize, defaultSamples);
	m_GoAltData = std::make_unique<DataCollector<GameObject3DAlt>>(arraySize, defaultSamples);

	ImGui::PlotConfig defaultConfig{};
	defaultConfig.frame_size = { 200.f, 100.f };
	defaultConfig.scale.min = 0;
	defaultConfig.tooltip.show = true;
	defaultConfig.line_thickness = 2.f;
	defaultConfig.grid_y.show = false;

	// Format: A B G R 
	constexpr ImU32 yellow{ 0xFF00FFFF }; 
	m_IntConfig = defaultConfig;
	m_IntConfig.values.color = yellow;

	constexpr ImU32 cyan{ 0xFFFFFF00 };
	m_GOConfig = defaultConfig;
	m_GOConfig.values.color = cyan;

	constexpr ImU32 magenta{0xFFFF00FF};
	m_GOAltConfig = defaultConfig;
	m_GOAltConfig.values.color = magenta;

	m_Colors[0] = cyan;
	m_Colors[1] = magenta;

	m_CombinedConfig = defaultConfig;
	m_CombinedConfig.values.ys_count = 2;
	m_CombinedConfig.values.colors = m_Colors;
}

void ThrowawayPlotsClass::Render()
{
	ImGui::Begin("Exercise 1");
	ImGui::InputInt("# samples", &m_IntData->GetSamplesMutable(), 1, 10);
	if (ImGui::Button("Trash the cache"))
	{
		RunIntDataCollection();
	}

	if(!m_IntMeansFloat.empty())
	{
		ImGui::Plot("int plot", m_IntConfig);
	}

	ImGui::End();

	ImGui::Begin("Exercise 2");
	ImGui::InputInt("# GameObject samples", &m_GoData->GetSamplesMutable(), 1, 10);
	if (ImGui::Button("Trash the cache with GameObject3D"))
	{
		RunGO3DDataCollection();
	}
	if (!m_GOMeansFloat.empty())
	{
		ImGui::Plot("GameObject3D plot", m_GOConfig);
	}

	ImGui::InputInt("# GameObjectAlt samples", &m_GoAltData->GetSamplesMutable(), 1, 10);
	if (ImGui::Button("Trash the cache with GameObject3DAlt"))
	{
		RunGO3DALTDataCollection();
	}
	if (!m_GOAltMeansFloat.empty())
	{
		ImGui::Plot("GameObject3DAlt plot", m_GOAltConfig);
	}

	if(!(m_GOMeansFloat.empty() || m_GOAltMeansFloat.empty()))
	{
		ImGui::Text("Combined:");
		m_CombinedConfig.values.ys_list = m_CombinedArray;
		m_CombinedConfig.values.count = m_GOConfig.values.count;
		m_CombinedConfig.scale.max = m_GOConfig.scale.max;
		ImGui::Plot("Combined GameObject Plots", m_CombinedConfig);
	}
	ImGui::End();
}

void ThrowawayPlotsClass::RunIntDataCollection()
{
	m_IntMeansFloat.clear();
	if(!m_IntData->Run()) return;
	for (const auto elem : m_IntData->GetMeans())
	{
		m_IntMeansFloat.push_back(static_cast<float>(elem));
	}

	UpdateConfig(m_IntConfig, m_IntMeansFloat);
}

void ThrowawayPlotsClass::RunGO3DDataCollection()
{
	m_GOMeansFloat.clear();
	if(!m_GoData->Run()) return;
	for(const auto elem : m_GoData->GetMeans())
	{
		m_GOMeansFloat.push_back(static_cast<float>(elem));
	}

	UpdateConfig(m_GOConfig, m_GOMeansFloat);
	m_CombinedArray[0] = m_GOMeansFloat.data();
}

void ThrowawayPlotsClass::RunGO3DALTDataCollection()
{
	m_GOAltMeansFloat.clear();
	if(!m_GoAltData->Run()) return;
	for (const auto elem : m_GoAltData->GetMeans())
	{
		m_GOAltMeansFloat.push_back(static_cast<float>(elem));
	}

	UpdateConfig(m_GOAltConfig, m_GOAltMeansFloat);
	m_CombinedArray[1] = m_GOAltMeansFloat.data();
}

void ThrowawayPlotsClass::UpdateConfig(ImGui::PlotConfig& config, const std::vector<float>& values)
{
	config.values.ys = values.data();
	config.values.count = static_cast<int>(values.size());
	config.scale.max = *std::ranges::max_element(values);
}