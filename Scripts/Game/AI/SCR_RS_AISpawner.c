class SCR_RS_AISpawner
{
	// Default Constructor
	void SCR_RS_AISpawner()
	{
		
	}
	
	// Default Destructor
	void ~SCR_RS_AISpawner()
	{
		
	}
	
	void AISpawner(string spawnGroup, vector spawnPosition, string waypointType, vector waypointPosition)
	{
		// Generate the resource 
		Resource resource = GenerateAndValidateResource(spawnGroup);
		
		if (!resource)
		{
			Print(("[AI Spawner] Unable able to load resource for the spawn group: " + spawnGroup), LogLevel.ERROR);
			return;
		}
		
		// Generate the spawn parameters and spawn the group 
		SCR_AIGroup group = SCR_AIGroup.Cast(GetGame().SpawnEntityPrefab(resource, null, GenerateSpawnParameters(spawnPosition)));
		
		if (!group)
		{
			Print("[AI Spawner] Unable to spawn group!", LogLevel.ERROR);
			return;
		}
		
		// Create a waypoint for this group
		CreateWaypoint(group, waypointType, waypointPosition);
	}
	
	protected void CreateWaypoint(SCR_AIGroup group, string waypointType, vector waypointPosition)
	{
		// Generate the resource 
		Resource resource = GenerateAndValidateResource(waypointType);
		
		if (!resource)
		{
			Print(("[Create Waypoint] Unable able to load resource for the waypoint: " + waypointType), LogLevel.ERROR);
			return;
		}
		
		// Generate the spawn parameters and create the waypoint 
		AIWaypoint waypoint = AIWaypoint.Cast(GetGame().SpawnEntityPrefab(resource, null, GenerateSpawnParameters(waypointPosition)));
		
		if (!waypoint)
		{
			Print("[Create Waypoint] Unable to create waypoint!", LogLevel.ERROR);
			return;
		}
		
		// Assign the waypoint to the group 
		group.AddWaypoint(waypoint);
	}
	
	protected Resource GenerateAndValidateResource(string resourceToLoad)
	{
		// Load the resource 
		Resource resource = Resource.Load(resourceToLoad);
		
		// Validate the prefab and show an appropriate error if invalid 
		if (!resource.IsValid())
		{
			Print(("[Generate And Validate Resource] Resource is invalid: " + resourceToLoad), LogLevel.ERROR);
			return null;
		}
		
		// Return the resource 
		return resource;
	}
	
	protected EntitySpawnParams GenerateSpawnParameters(vector position)
	{
		// Create a new set of spawn parameters 
		EntitySpawnParams params = EntitySpawnParams();
		params.TransformMode = ETransformMode.WORLD;
		
		// Assign the position to those parameters 
		params.Transform[3] = position;
		
		// Return this set of spawn parameters
		return params;
	}
};