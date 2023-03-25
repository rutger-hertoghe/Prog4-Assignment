#ifndef DATACOLLECTOR_H
#define DATACOLLECTOR_H

#include <vector>
#include <chrono>
#include <numeric>
#include <iostream>

struct Transform
{
    float matrix[16] = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1 };
};

class GameObject3D
{
public:
    Transform transform;
    int ID;
};

class GameObject3DAlt
{
public:
    Transform* transform;
    int ID;
};

template<typename T>
class DataCollector final
{
public:
	explicit DataCollector<T>(int arraySize, int samples);
	~DataCollector();

	DataCollector(const DataCollector& other) = delete;
	DataCollector(DataCollector&& other) = delete;
	DataCollector& operator=(const DataCollector& other) = delete;
	DataCollector& operator=(DataCollector&& other) = delete;

	[[nodiscard]] const std::vector<std::vector<int>>& GetMeasurements() const;
	[[nodiscard]] const std::vector<int>& GetMeans() const;

    bool Run();

    int& GetSamplesMutable();

private:
	int m_ArraySize;
	T* m_TypeArray;

	int m_Samples;

	std::vector<std::vector<int>> m_Measurements;
	std::vector<int> m_Means;

	void MeasureCacheSpeeds();
	void RemoveOutliers();
	void CalculateMeans();
    void DoManipulation(T& arrayMember);
};

template<typename T>
DataCollector<T>::DataCollector(int arraySize, int samples)
    : m_ArraySize(arraySize)
    , m_Samples(samples)
{
    m_TypeArray = new T[m_ArraySize];
}

template<typename T>
DataCollector<T>::~DataCollector()
{
    delete[] m_TypeArray;
}

template<typename T>
const std::vector<std::vector<int>>& DataCollector<T>::GetMeasurements() const
{
    return m_Measurements;
}

template<typename T>
const std::vector<int>& DataCollector<T>::GetMeans() const
{
    return m_Means;
}

template<typename T>
bool DataCollector<T>::Run()
{
    m_Measurements.clear();
    m_Means.clear();
    if(m_Samples < 3)
    {
        std::cout << "Amount of samples specified is too small! Must be at least 3\n";
        return false;
    }
    MeasureCacheSpeeds();
    RemoveOutliers();
    CalculateMeans();
    return true;
}

template<typename T>
int& DataCollector<T>::GetSamplesMutable()
{
    return m_Samples;
}

template<typename T>
void DataCollector<T>::MeasureCacheSpeeds()
{
    for (int measurement{ 0 }; measurement < m_Samples; ++measurement)
    {
        std::vector<int> row;
        for (int stepSize{ 1 }; stepSize <= 1024; stepSize *= 2)
        {
            auto start{ std::chrono::high_resolution_clock::now() };
            for (int idx{ 0 }; idx < m_ArraySize; idx += stepSize)
            {
                DoManipulation(m_TypeArray[idx]);
            }
            auto end{ std::chrono::high_resolution_clock::now() };
            const auto deltaTime{ std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() };

            row.push_back(static_cast<int>(deltaTime));
        }
        m_Measurements.push_back(row);
    }
}

template<typename T>
void DataCollector<T>::RemoveOutliers()
{
    std::vector<int> sumVec;
    sumVec.reserve(m_Measurements.size());

    for (const auto& measure : m_Measurements)
    {
        sumVec.push_back(std::accumulate(measure.begin(), measure.end(), 0));
    }

    // max outlier
    auto it{ std::max_element(sumVec.begin(), sumVec.end()) };
    auto indexToRemove{ static_cast<int>(it - sumVec.begin()) };
    m_Measurements.erase(m_Measurements.begin() + indexToRemove);
    sumVec.erase(sumVec.begin() + indexToRemove);

    // min outlier
    it = std::min_element(sumVec.begin(), sumVec.end());
    indexToRemove = static_cast<int>(it - sumVec.begin());
    m_Measurements.erase(m_Measurements.begin() + indexToRemove);
    sumVec.erase(sumVec.begin() + indexToRemove);
}

template<typename T>
void DataCollector<T>::CalculateMeans()
{
    const int samples{ static_cast<int>(m_Measurements.size()) };
    const int rowLength{ static_cast<int>(m_Measurements[0].size()) };
    for (int elementIdx{ 0 }; elementIdx < rowLength; ++elementIdx)
    {
        int sum{ 0 };
        for (int rowIdx{ 0 }; rowIdx < samples; ++rowIdx)
        {
            sum += m_Measurements[rowIdx][elementIdx];
        }
        int mean = sum / samples;
        m_Means.push_back(mean);
    }
}

template<typename T>
void DataCollector<T>::DoManipulation(T& arrayMember)
{
}

template<>
inline void DataCollector<int>::DoManipulation(int& arrayMember)
{
    arrayMember *= 2;
}

template<>
inline void DataCollector<GameObject3D>::DoManipulation(GameObject3D& arrayMember)
{
    arrayMember.ID *= 2;
}

template<>
inline void DataCollector<GameObject3DAlt>::DoManipulation(GameObject3DAlt& arrayMember)
{
    arrayMember.ID *= 2;
}
#endif