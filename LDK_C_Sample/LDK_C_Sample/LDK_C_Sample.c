// LDK_C_Sample.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdio.h>
#include <stdlib.h>
#include "hasp_api.h"
#include "all-var.h"

//void FeatureLogin();
//void Logout();
//void GetFingerprint();
//void ApplyV2CP();
//void GetSessionInfo();
//
//hasp_handle_t handle = HASP_INVALID_HANDLE_VALUE;
//hasp_status_t status;
//hasp_feature_t FeatureId;
//
//
//unsigned char vendor_code[] =
//"AzIceaqfA1hX5wS+M8cGnYh5ceevUnOZIzJBbXFD6dgf3tBkb9cvUF/Tkd/iKu2fsg9wAysYKw7RMAsV"
//"vIp4KcXle/v1RaXrLVnNBJ2H2DmrbUMOZbQUFXe698qmJsqNpLXRA367xpZ54i8kC5DTXwDhfxWTOZrB"
//"rh5sRKHcoVLumztIQjgWh37AzmSd1bLOfUGI0xjAL9zJWO3fRaeB0NS2KlmoKaVT5Y04zZEc06waU2r6"
//"AU2Dc4uipJqJmObqKM+tfNKAS0rZr5IudRiC7pUwnmtaHRe5fgSI8M7yvypvm+13Wm4Gwd4VnYiZvSxf"
//"8ImN3ZOG9wEzfyMIlH2+rKPUVHI+igsqla0Wd9m7ZUR9vFotj1uYV0OzG7hX0+huN2E/IdgLDjbiapj1"
//"e2fKHrMmGFaIvI6xzzJIQJF9GiRZ7+0jNFLKSyzX/K3JAyFrIPObfwM+y+zAgE1sWcZ1YnuBhICyRHBh"
//"aJDKIZL8MywrEfB2yF+R3k9wFG1oN48gSLyfrfEKuB/qgNp+BeTruWUk0AwRE9XVMUuRbjpxa4YA67SK"
//"unFEgFGgUfHBeHJTivvUl0u4Dki1UKAT973P+nXy2O0u239If/kRpNUVhMg8kpk7s8i6Arp7l/705/bL"
//"Cx4kN5hHHSXIqkiG9tHdeNV8VYo5+72hgaCx3/uVoVLmtvxbOIvo120uTJbuLVTvT8KtsOlb3DxwUrwL"
//"zaEMoAQAFk6Q9bNipHxfkRQER4kR7IYTMzSoW5mxh3H9O8Ge5BqVeYMEW36q9wnOYfxOLNw6yQMf8f9s"
//"JN4KhZty02xm707S7VEfJJ1KNq7b5pP/3RjE0IKtB2gE6vAPRvRLzEohu0m7q1aUp8wAvSiqjZy7FLaT"
//"tLEApXYvLvz6PEJdj4TegCZugj7c8bIOEqLXmloZ6EgVnjQ7/ttys7VFITB3mazzFiyQuKf4J6+b/a/Y";


int main() {

    int choice;

    // The do-while loop ensures the menu runs at least once
    do {
        // Display the menu
        printf("\n--- Sentinel LDK Operations ---\n");
        printf("1. Login\n");
        printf("2. Logout\n");
		printf("3. Get Fingerprint\n");
		printf("4. Apply V2CP\n");
        printf("5. Get Session Info\n");
        printf("6. read function\n");
        printf("7. write function (press 7, write data and then enter)\n");
        printf("9. Exit\n");
        printf("Enter your choice (1-7, 9 to exit): ");
        scanf_s("%d", &choice);

        // Perform operation based on the selected number
        switch (choice) {
        case 1:
            FeatureLogin();
            break;
        case 2:
            Logout();
            break;
        case 3:
            GetFingerprint();
            break;
        case 4:
            ApplyV2CP();
            break;
        case 5:
            GetSessionInfo();
            break;
		case 6:
			read();
			break;
        case 7:
            write();
            break;
        case 9:
            printf("Exiting the program. Goodbye!\n");
            break;
        default:
            printf("Invalid choice! Please select a number between 1 and 4.\n");
        }

    } while (choice != 9); // The loop continues until the user inputs 9    
}




void FeatureLogin()
{
    const char* scope =
        "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"
        "<haspscope/>";

    printf("\nEnter Featureid : ");
    scanf_s("%u", &FeatureId);
    status = hasp_login_scope(FeatureId, scope, vendor_code, &handle);

    /* check if operation was successful */
    if (status != HASP_STATUS_OK)
    {
		printf("\nlogin failed on FeatureId %lu and Status code is %d \n", FeatureId, status);
    }
    else
    {
        printf("login success on FeatureId %lu\n", FeatureId);
    }
    

}



void Logout()
{
    status = hasp_logout(handle);
    if (status != HASP_STATUS_OK)
    {
        printf("\nLogout failed on FeatureId %lu and Status code is %d \n", FeatureId, status);
    }
    else
    {
        printf("Logout success on FeatureId %lu\n", FeatureId);
    }
}




void GetFingerprint()
{
    char* info = 0;
    FILE* fp = NULL;
    errno_t err;

    const char* scope =
        "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"
        "<haspscope>"
        "    <license_manager hostname=\"localhost\" />"
        "</haspscope>";

    const char* format =
        "<haspformat format=\"host_fingerprint\"/>";

    status = hasp_get_info(scope, format, vendor_code, &info);

    /* check if operation was successful */
    if (status != HASP_STATUS_OK)
    {
        printf("\n Fingerprint call failed with Status code %d \n", status);
    }
    else
    {
        printf("\n Fingerprint call success \n");
        printf("Fingerprint: %s\n", info);

        /* Open file for writing */
        err = fopen_s(&fp, "fingerprint", "w");
        
        if (err == 0 && fp != NULL)
        {
            /* Write the fingerprint to file */
            fprintf(fp, "%s", info);
            fclose(fp);
            printf("Fingerprint saved to file 'fingerprint'\n");
        }
        else
        {
            printf("Failed to create/open fingerprint file\n");
        }
    }

    /* use the information, free it afterwards */
    hasp_free(info);
}



void ApplyV2CP()
{
    // 1. Define file path and variables
    const char* v2c_filename = "update.v2cp";
    char* v2c_buffer = NULL;
    long file_size = 0;
    FILE* file = NULL;
    hasp_status_t status;
    char* acknowledge_data = NULL;

    // 2. Open the V2C file in binary read mode
    file = fopen(v2c_filename, "rb");
    if (file == NULL) {
        perror("Error opening V2C file");
        return;
    }

    // 3. Determine the size of the file
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (file_size <= 0) {
        printf("Error: V2C file is empty.\n");
        fclose(file);
        return;
    }

    // 4. Allocate memory for the buffer (+1 for null-terminator if needed by API)
    v2c_buffer = (char*)malloc(file_size + 1);
    if (v2c_buffer == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return;
    }

    // 5. Read file contents into the buffer
    size_t bytes_read = fread(v2c_buffer, 1, file_size, file);
    if (bytes_read != file_size) {
        printf("Error reading the complete V2C file.\n");
        free(v2c_buffer);
        fclose(file);
        return;
    }
    v2c_buffer[file_size] = '\0'; // Null-terminate the string buffer
    fclose(file);

    printf("Successfully read %ld bytes from %s\n", file_size, v2c_filename);

    // 6. Call the Sentinel HASP update API
    // The acknowledge_data will store the V2C receipt if successful
    status = hasp_update(v2c_buffer, &acknowledge_data);

    // 7. Check the API execution status
    if (status == HASP_STATUS_OK) {
        printf("Update applied successfully!\n");
        if (acknowledge_data != NULL) {
            printf("Acknowledge receipt generated successfully.\n");
            // Optional: Save acknowledge_data to a .v2cp receipt file here
        }
    }
    else {
        printf("Failed to apply update. HASP Error Code: %d\n", status);
    }

    // 8. Clean up allocated resources
    if (v2c_buffer != NULL) {
        free(v2c_buffer);
    }
    if (acknowledge_data != NULL) {
        hasp_free(acknowledge_data); // Use HASP API's native memory management
    }
}


void GetSessionInfo()
{
    char* info = 0;
    status = hasp_get_sessioninfo(handle, HASP_SESSIONINFO, &info);
    /* check if operation was successful */
    if (status != HASP_STATUS_OK)
    {
        printf("\n GetSessionInfo call failed with Status code %d \n", status);
    }
    else
    {
        printf("\n\n GetSessionInfo call success \n");
        printf("Session Info: %s\n", info);
    }
    /* use the information, free it afterwards */
    hasp_free(info);
}

void read()
{
	hasp_size_t offset = 0;
	hasp_size_t len = 48; // Specify the length of data to read
    unsigned char data[48];
    status = hasp_read(handle, HASP_FILEID_RW, offset, len, data);
    /* check if operation was successful */
    if (status != HASP_STATUS_OK)
    {
        printf("\n Read call failed with Status code %d \n", status);
    }
    else
    {
        printf("\n Read call success \n");
        printf("Read Info: %s\n", data);
    }    
}


//void write()
//{
//    hasp_size_t offset = 0;
//    hasp_size_t len = 48; // Specify the length of data to write
//    unsigned char data[48] = "This is a test data to write to the key.";
//    status = hasp_write(handle, HASP_FILEID_RW, offset, len, data);
//    /* check if operation was successful */
//    if (status != HASP_STATUS_OK)
//    {
//        printf("\n Write call failed with Status code %d \n", status);
//    }
//    else
//    {
//        printf("\n Write call success \n");
//        printf("Write Info: %s\n", data);
//    }    
//}


void write()
{
    hasp_size_t offset = 0;
    unsigned char data[256];

    printf("Enter data to write to the key: ");
    fgets((char*)data, sizeof(data), stdin);

    /* Remove trailing newline if present */
    data[strcspn((char*)data, "\n")] = '\0';

    hasp_size_t len = strlen((char*)data);

    status = hasp_write(handle, HASP_FILEID_RW, offset, len, data);

    /* Check if operation was successful */
    if (status != HASP_STATUS_OK)
    {
        printf("\nWrite call failed with Status code %d\n", status);
    }
    else
    {
        printf("\nWrite call succeeded\n");
        printf("Written Data: %s\n", data);
    }
}