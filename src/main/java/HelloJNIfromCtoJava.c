#include <string.h>
#include <jni.h>

#ifdef _WIN32
#define PATH_SEPARATOR ';'
#else
#define PATH_SEPARATOR ':'
#endif

int main()
{
	JavaVMOption options[1];
	JNIEnv *env;
	JavaVM *jvm;
	JavaVMInitArgs vm_args;
	long status;
	jclass cls;
	jmethodID mid;
	jint square;
	jboolean not;
	jint printit;

	options[0].optionString = "-Djava.class.path=./GlobalSnapshot-1.0-SNAPSHOT.jar:./GlobalSnapshot-1.0-SNAPSHOT-jar-with-dependencies.jar";

	memset(&vm_args, 0, sizeof(vm_args));
	vm_args.version = JNI_VERSION_1_8;
	vm_args.nOptions = 1;
	vm_args.options = options;
	status = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
	
	printf("Hi, this is C code talking..\n");

	if (status != JNI_ERR)
	{
		printf("Finding Java Class...\n");
		cls = (*env)->FindClass(env, "nl/tue/ds/ServerLauncher");
		if(cls !=0)
		{
			printf("cls != 0\n");

			mid = (*env)->GetStaticMethodID(env, cls, "main", "([Ljava/lang/String;)V");
			if(mid !=0)
			{
				printit = (*env)->CallStaticBooleanMethod(env, cls, mid);
				printf("mid != 0\n");
			}
			else
			{
				printf("mid == 0\n");

			}

		}
		else
		{
			printf("cls == 0\n");
		}		

		

		(*jvm)->DestroyJavaVM(jvm);
		return 0;
	}
	else
		printf("ERROR !\n");
		return -1;
}
