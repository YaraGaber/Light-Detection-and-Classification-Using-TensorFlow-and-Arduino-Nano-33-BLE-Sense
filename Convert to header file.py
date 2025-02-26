# Convert .tflite model to a C header file
with open('light_model.tflite', 'rb') as f:
    tflite_model = f.read()

with open('model.h', 'w') as f:
    f.write('#include <stdint.h>\n')
    f.write('const uint8_t g_model[] = {')
    f.write(','.join(f'0x{byte:02x}' for byte in tflite_model))
    f.write('};')
