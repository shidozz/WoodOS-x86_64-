#include <stdint.h>
#include <stddef.h>

// Adresses des registres de contrôle du codec AC-97
#define AC97_CONTROL_REG 0x00
#define AC97_STATUS_REG 0x02
#define AC97_VOLUME_LEFT_REG 0x04
#define AC97_VOLUME_RIGHT_REG 0x06

// Valeurs de contrôle pour l'initialisation du codec AC-97
#define AC97_CONTROL_INIT 0x0001
#define AC97_STATUS_INIT 0x0100

// Masques de bits pour l'extraction des données du registre de statut
#define AC97_STATUS_READY_MASK 0x0100

#define AC97_STATUS_CODEC_READY_MASK 0x0001
// Fonction d'initialisation du codec AC-97
void ac97_init() {
  // Écrire la valeur de contrôle d'initialisation dans le registre de contrôle
  write_register(AC97_CONTROL_REG, AC97_CONTROL_INIT);

  // Attendre que le codec soit prêt
  while ((read_register(AC97_STATUS_REG) & AC97_STATUS_READY_MASK) == 0) {
    // Boucle vide
  }

  // Écrire la valeur de statut d'initialisation dans le registre de statut
  write_register(AC97_STATUS_REG, AC97_STATUS_INIT);

  // Attendre que le codec soit prêt
  while ((read_register(AC97_STATUS_REG) & AC97_STATUS_CODEC_READY_MASK) == 0) {
    // Boucle vide
  }
}

// Fonction de configuration du volume des canaux gauche et droit
void ac97_set_volume(uint8_t left, uint8_t right) {
  // Écrire la valeur du volume du canal gauche dans le registre approprié
  write_register(AC97_VOLUME_LEFT_REG, left);

  // Écrire la valeur du volume du canal droit dans le registre approprié
  write_register(AC97_VOLUME_RIGHT_REG, right);
}

int main(void) {
  // Initialiser le codec AC-97
  ac97_init();

  // Configurer le volume des canaux gauche et droit à 50%
  ac97_set_volume(0x8080, 0x8080);

  return 0;
}