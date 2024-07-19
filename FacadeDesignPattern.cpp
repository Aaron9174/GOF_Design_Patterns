/**
 * The facade design pattern describes how to solve such problems:
 * - To make a complex subsystem easier to use, a simple interface should be provided for a set of interfaces in the subsystem
 * - The dependencies on a subsystem should be minimized
 * Credit for proof of concept:
 * https://en.wikipedia.org/wiki/Facade_pattern
 */

#include <cstdint>

/**
 * More complicated classes that require more knowledge to use
 */
struct CPU {
  void freeze();
  void jump(long position);
  void execute();
};
struct HardDrive {
  char* read(long lba, uint32_t size);
};
struct Memory {
  void load(long position, char* data);
};

/**
 * The more simplified class for the client/user to leverage
 */
class ComputerFacade {
  const uint32_t K_BOOT_ADDRESS = 0xBEEF;
  char* K_SECTOR_SIZE  = "Test";

  public:
    void start() {
      _cpu.freeze();
      _memory.load(K_BOOT_ADDRESS, K_SECTOR_SIZE);
      _cpu.jump(K_BOOT_ADDRESS);
      _cpu.execute();
    }
  
  private:
    CPU _cpu;
    Memory _memory;
    HardDrive _hardDrive;
};

int main() {
  ComputerFacade computer;
  computer.start();
}