# Banker's Algorithm Explanation

The Banker's Algorithm is a deadlock avoidance algorithm that ensures safe allocation of resources to processes. It checks whether a resource request would leave the system in a safe state where deadlock cannot occur.

## Algorithm Steps

### 1. Data Structures
- **Available**: Vector of available resources of each type
- **Max**: Maximum demand of each process
- **Allocation**: Resources currently allocated to each process
- **Need**: Remaining resources needed by each process (Need = Max - Allocation)

### 2. Safety Algorithm
1. Initialize Work = Available and Finish[i] = false for all processes
2. Find a process Pᵢ such that:
   - Finish[i] = false
   - Need[i] ≤ Work
3. If such process exists:
   - Work = Work + Allocation[i]
   - Finish[i] = true
   - Repeat from step 2
4. If all processes have Finish[i] = true, system is safe

# The answer to the question in the assignment doc

## Is the system in a safe state?

The answer is 'Yes' for the given safe_input.txt snapshot of the system at time t0 :

- Total Resource Instances: A = 10, B = 5, C = 7
- Available: A = 3, B = 2, C = 2
- The algorithm finds a safe sequence where all processes can complete without deadlock

- The safe sequence: P3 → P1 → P0 → P2 → P4

### Sample Outputs Screenshot file:
Sample Outputs/sample_outputs.png