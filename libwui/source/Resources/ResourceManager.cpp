#include <Libwui/Resources/ResourceManager.h>
#include <vector>

using namespace std;
using namespace Libwui::Resources;

ResourceManager::ResourceManager()
  : _cacheLimit(100)
{}

ResourceManager& ResourceManager::Current()
{
	static ResourceManager r;
	return r;
}

Resource* ResourceManager::GetResource(const string& key)
{
	if(Current()._resources.find(key) == Current()._resources.end())
		return NULL;

	Current()._cacheCount[key] = 0;
	return Current()._resources[key];
}

void ResourceManager::AddResource(const std::string& key, Resource* res)
{
	Current()._cacheCount[key] = 0;
	Current()._resources[key] = res;
}

void ResourceManager::Clean(bool force)
{
	vector<string> toDelete;

	for(map<string,u32>::iterator ite = Current()._cacheCount.begin(); ite != Current()._cacheCount.end(); ite++)
		if(ite->second > Current()._cacheLimit || force)
		{
			if(Current()._resources[ite->first]->isDefault==false)
			{
				delete Current()._resources[ite->first];
				Current()._resources.erase(ite->first);
				toDelete.push_back(ite->first);
			}
		}

	for(vector<string>::iterator ite = toDelete.begin(); ite != toDelete.end(); ite++)
		Current()._cacheCount.erase(*ite);
}

void ResourceManager::SetCacheDuration(u32 frameCount)
{
	Current()._cacheLimit = frameCount;
}
