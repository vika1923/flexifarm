// Include libraries for random numbers and time
#include <cstdlib>   // For rand() function (random numbers)
#include <ctime>     // For time() function (random seed)

/**
 * IncubatorSimulator Class
 * Part of a farming system - simulates egg incubation process
 * Returns data to the main farming system instead of printing reports
 */
class IncubatorSimulator {
private:
    // ========== CONSTANTS ==========
    static const int MAX_EGGS = 20;           // Maximum number of eggs to generate
    static const int MIN_EGGS = 5;            // Minimum number of eggs to generate
    
    // ========== INSTANCE VARIABLES ==========
    int totalEggs;              // Total number of eggs generated
    int fertilizedEggs;         // Number of fertilized eggs
    int notFertilizedEggs;      // Number of not fertilized eggs
    int eggsInIncubator;        // Number of eggs loaded in incubator
    int hatchedChicks;          // Number of successfully hatched chicks
    int failedToHatch;          // Number of eggs that didn't hatch
    double successRate;         // Percentage of successful hatches
    
    // Arrays to track egg status
    bool eggHealthStatus[MAX_EGGS];   // true = fertilized, false = not fertilized
    bool eggInIncubator[MAX_EGGS];    // true = in incubator, false = not
    
    // Default incubator settings
    double temperature;         // Incubator temperature (37.5 Celsius)
    double humidity;            // Incubator humidity (55%)
    
    /**
     * Generate random eggs with random fertilization status
     */
    void generateEggs() {
        // Generate random number of eggs between 5-20
        totalEggs = (rand() % (MAX_EGGS - MIN_EGGS + 1)) + MIN_EGGS;
        
        // Initialize counters
        fertilizedEggs = 0;
        notFertilizedEggs = 0;
        
        // Initialize arrays
        for (int i = 0; i < MAX_EGGS; i++) {
            eggHealthStatus[i] = false;
            eggInIncubator[i] = false;
        }
        
        // Randomly assign fertilization status to each egg
        for (int i = 0; i < totalEggs; i++) {
            bool isFertilized = (rand() % 2 == 0);  // 50% chance
            eggHealthStatus[i] = isFertilized;
            
            if (isFertilized) {
                fertilizedEggs++;
            } else {
                notFertilizedEggs++;
            }
        }
    }
    
    /**
     * Load fertilized eggs into the incubator
     */
    void loadIncubator() {
        // Only proceed if we have fertilized eggs
        if (fertilizedEggs == 0) {
            eggsInIncubator = 0;
            return;
        }
        
        // Randomly select how many fertilized eggs to load (1 to all)
        int eggsToLoad = (rand() % fertilizedEggs) + 1;
        eggsInIncubator = 0;
        
        // Load fertilized eggs into incubator
        for (int i = 0; i < totalEggs && eggsInIncubator < eggsToLoad; i++) {
            if (eggHealthStatus[i]) {  // If egg is fertilized
                eggInIncubator[i] = true;
                eggsInIncubator++;
            }
        }
    }
    
    /**
     * Setup incubator environment with default optimal values
     */
    void setupConditions() {
        temperature = 37.5;  // Optimal temperature for chicken eggs
        humidity = 55.0;     // Optimal humidity percentage
    }
    
    /**
     * Simulate hatching process
     */
    void performHatching() {
        hatchedChicks = 0;
        
        // Check each egg in the incubator
        for (int i = 0; i < totalEggs; i++) {
            if (eggInIncubator[i]) {
                // 85% success rate for hatching
                bool hatched = (rand() % 100 < 85);
                
                if (hatched) {
                    hatchedChicks++;
                }
            }
        }
        
        // Calculate number that failed to hatch
        failedToHatch = eggsInIncubator - hatchedChicks;
        
        // Calculate success rate
        if (eggsInIncubator > 0) {
            successRate = ((double)hatchedChicks / eggsInIncubator) * 100.0;
        } else {
            successRate = 0.0;
        }
    }
    
public:
    /**
     * Constructor - Initialize all variables
     */
    IncubatorSimulator() {
        totalEggs = 0;
        fertilizedEggs = 0;
        notFertilizedEggs = 0;
        eggsInIncubator = 0;
        hatchedChicks = 0;
        failedToHatch = 0;
        successRate = 0.0;
        temperature = 0.0;
        humidity = 0.0;
    }
    
    /**
     * Run the complete incubation simulation
     * No user input required - uses default values
     */
    void runSimulation() {
        // Step 1: Generate eggs
        generateEggs();
        
        // Step 2: Load eggs into incubator
        loadIncubator();
        
        // Step 3: Setup conditions
        setupConditions();
        
        // Step 4: Perform hatching
        performHatching();
    }
    
    // ========== GETTER METHODS - Return values for main farming system ==========
    
    /**
     * Get total number of eggs generated
     */
    int getTotalEggs() {
        return totalEggs;
    }
    
    /**
     * Get number of fertilized eggs
     */
    int getFertilizedEggs() {
        return fertilizedEggs;
    }
    
    /**
     * Get number of not fertilized eggs
     */
    int getNotFertilizedEggs() {
        return notFertilizedEggs;
    }
    
    /**
     * Get number of eggs loaded in incubator
     */
    int getEggsInIncubator() {
        return eggsInIncubator;
    }
    
    /**
     * Get number of successfully hatched chicks
     */
    int getHatchedChicks() {
        return hatchedChicks;
    }
    
    /**
     * Get number of eggs that failed to hatch
     */
    int getFailedToHatch() {
        return failedToHatch;
    }
    
    /**
     * Get success rate as percentage
     */
    double getSuccessRate() {
        return successRate;
    }
    
    /**
     * Get incubator temperature
     */
    double getTemperature() {
        return temperature;
    }
    
    /**
     * Get incubator humidity
     */
    double getHumidity() {
        return humidity;
    }
};
