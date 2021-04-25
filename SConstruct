import os
SetOption('warn', ['no-duplicate-environment'] + GetOption('warn'))
plf ={
    'le501x': ('arm_cm','cortex-m0'),
    'sagi': ('arm_cm','cortex-m3'),
    'taurus': ('rv32','e902'),
}
ic = ARGUMENTS.get('ic','le501x')
base_arch,cpu = plf[ic]
default_toolchain = {
    'arm_cm': 'arm-gcc',
    'rv32': 'riscv-gcc',
}
tool = ARGUMENTS.get('toolchain',default_toolchain[base_arch])
env = Environment(ENV = os.environ,tools=[tool],toolpath=['tools'])
print(env['TOOLS'])
env['IC'] = ic
env['CPU'] = cpu
env['BASE_ARCH'] = base_arch
env.VariantDir('build/$IC', '.',duplicate=0)

if env['IC'] == 'le501x':
    env['CPU'] = 'cortex-m0'
    env['STACK_BIN_OUTPUT_DIR'] = Dir('#dev/soc/arm_cm/le501x/bin/')
elif env['IC'] == 'sagi':
    env['CPU'] = 'cortex-m3'
    env['STACK_BIN_OUTPUT_DIR'] = Dir('#dev/soc/arm_cm/sagi/bin/')
elif env['IC'] == 'taurus':
    env['ARCH'] = 'rv32emc'
    env['ABI'] = 'ilp32e'
    env['STACK_BIN_OUTPUT_DIR'] = Dir('#dev/soc/arm_cm/taurus/bin/')

if env['BASE_ARCH'] == 'rv32':
    env['ARCH_FLAGS'] = ' -mabi=$ABI -march=$ARCH -mshorten-memrefs -mstrict-align -msave-restore -msmall-data-limit=0 '
    env['AS_ARCH_FLAGS'] = ' -mabi=$ABI -march=$ARCH '
    env['LD_ARCH_FLAGS'] = ' -mccrt '
else:
    env['ARCH_FLAGS'] = ' -mabi=aapcs -mthumb -mcpu=$CPU -mno-unaligned-access -fshort-enums -fshort-wchar '
    env['LD_ARCH_FLAGS'] = ' -Wl,--no-wchar-size-warning -Wl,--no-enum-size-warning -specs=nosys.specs '

if 'mdk' in env['TOOLS']:
    env['COMPILER'] = 'armcc'
    
else:
    env['COMPILER'] = 'gnu'
    env['CFLAGS'] = '${ARCH_FLAGS} -Os -std=c11 -g -ffunction-sections -fdata-sections -fstrict-volatile-bitfields -fno-common -fno-optimize-sibling-calls -Wall'
    env['ASFLAGS'] = '${AS_ARCH_FLAGS} -g '
    env['LINKFLAGS'] = '${ARCH_FLAGS} -Os -std=c11 -g -specs=nano.specs -T ${LINKSCRIPT} -Wl,-Map=${TARGET.base}.map -Wl,--cref ${LD_ARCH_FLAGS} '
    env['GC_OPTION'] = ' -Wl,--gc-sections '

env['CPPDEFINES'] = ['-D{}'.format(env['IC'].upper())]

env.SConscript('build/$IC/dev/SConscript',exports=['env'])