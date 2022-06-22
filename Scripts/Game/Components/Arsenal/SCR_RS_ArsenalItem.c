[BaseContainerProps(), SCR_BaseContainerCustomTitleResourceName("m_ItemResourceName", true)]
modded class SCR_ArsenalItem
{
	// We need a variable and a getter for that variable to control the spawn chance of this item
	[Attribute("25", UIWidgets.Slider, "Chance to Spawn", "0 100 1")]
	protected float m_ItemChanceToSpawn;
	
	// We need a variable and a getter for that variable to control the max number of items that can be created
	[Attribute("1", UIWidgets.Slider, "Max # to Spawn", "1 25 1")]
	protected int m_ItemMaxSpawnCount;
	
	float GetItemChanceToSpawn()
	{
		return m_ItemChanceToSpawn;
	}
	
	int GetItemMaxSpawnCount()
	{
		return m_ItemMaxSpawnCount;
	}
};