#include <System.h>

namespace Cober {

	void System::AddEntity(Entity entity) {
		entities.push_back(entity);
	}

	void System::RemoveEntity(Entity entity) {
		entities.erase(std::remove_if(entities.begin(), entities.end(), [&entity](Entity other) {
			return entity == other;
		}), entities.end());
	}
}