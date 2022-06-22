class SCR_RS_RandomCrateStorageComponentClass: SCR_ArsenalComponentClass
{
	
};

class SCR_RS_RandomCrateStorageComponent: SCR_ArsenalComponent
{
	override bool GetFilteredArsenalItems(out notnull array<SCR_ArsenalItem> filteredArsenalItems, SCR_Faction faction = null)
	{
		if (!faction && !GetAssignedFaction(faction))
		{
			return false;
		}
		
		array<SCR_ArsenalItem> tempFilteredArsenalItems = faction.GetFilteredArsenalItems(m_eSupportedArsenalItemTypes, m_eSupportedArsenalItemModes);
		
		foreach (SCR_ArsenalItem item: tempFilteredArsenalItems)
		{
			// We want to check here if we're allowed to spawn this item, if not continue
			if (!CanSpawnItem(item))
				continue;
			
			// If we're allowed to spawn this item, then we want to pick a random number of this item to spawn
			for (int i = 1; i <= GetNumberToSpawn(item); i++)
			{
				filteredArsenalItems.Insert(item)
			}
		}
		
		return !filteredArsenalItems.IsEmpty();
	}
	
	override protected void OnItemRemoved(IEntity entity, BaseInventoryStorageComponent storage)
	{
		// We don't want anything to happen on item removal, as this is not going to be a self resupplying box
		return;
	}
	
	// We need a method here to evaluate whether or not an item can be spawned
	protected bool CanSpawnItem(SCR_ArsenalItem itemToSpawn)
	{
		float seedPercentage = Math.RandomFloat(0.001, 100);
		return (itemToSpawn.GetItemChanceToSpawn() >= seedPercentage);
	}
	
	// We need a method here to determine how many items to spawn
	protected int GetNumberToSpawn(SCR_ArsenalItem itemToSpawn)
	{
		int numToSpawn = Math.RandomInt(1, itemToSpawn.GetItemMaxSpawnCount());
		return numToSpawn;
	}
};