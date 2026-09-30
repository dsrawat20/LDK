using Aladdin.HASP;
using System;
using System.IO;
using System.Text;

namespace LDK_CS_licensing_Sample
{
     class Program
    {
        static Hasp? hasp;
        // Also change vendorCode to static to allow access from static FeatureLogin
        static string vendorCode =
            "AzIceaqfA1hX5wS+M8cGnYh5ceevUnOZIzJBbXFD6dgf3tBkb9cvUF/Tkd/iKu2fsg9wAysYKw7RMAsV" +
            "vIp4KcXle/v1RaXrLVnNBJ2H2DmrbUMOZbQUFXe698qmJsqNpLXRA367xpZ54i8kC5DTXwDhfxWTOZrB" +
            "rh5sRKHcoVLumztIQjgWh37AzmSd1bLOfUGI0xjAL9zJWO3fRaeB0NS2KlmoKaVT5Y04zZEc06waU2r6" +
            "AU2Dc4uipJqJmObqKM+tfNKAS0rZr5IudRiC7pUwnmtaHRe5fgSI8M7yvypvm+13Wm4Gwd4VnYiZvSxf" +
            "8ImN3ZOG9wEzfyMIlH2+rKPUVHI+igsqla0Wd9m7ZUR9vFotj1uYV0OzG7hX0+huN2E/IdgLDjbiapj1" +
            "e2fKHrMmGFaIvI6xzzJIQJF9GiRZ7+0jNFLKSyzX/K3JAyFrIPObfwM+y+zAgE1sWcZ1YnuBhICyRHBh" +
            "aJDKIZL8MywrEfB2yF+R3k9wFG1oN48gSLyfrfEKuB/qgNp+BeTruWUk0AwRE9XVMUuRbjpxa4YA67SK" +
            "unFEgFGgUfHBeHJTivvUl0u4Dki1UKAT973P+nXy2O0u239If/kRpNUVhMg8kpk7s8i6Arp7l/705/bL" +
            "Cx4kN5hHHSXIqkiG9tHdeNV8VYo5+72hgaCx3/uVoVLmtvxbOIvo120uTJbuLVTvT8KtsOlb3DxwUrwL" +
            "zaEMoAQAFk6Q9bNipHxfkRQER4kR7IYTMzSoW5mxh3H9O8Ge5BqVeYMEW36q9wnOYfxOLNw6yQMf8f9s" +
            "JN4KhZty02xm707S7VEfJJ1KNq7b5pP/3RjE0IKtB2gE6vAPRvRLzEohu0m7q1aUp8wAvSiqjZy7FLaT" +
            "tLEApXYvLvz6PEJdj4TegCZugj7c8bIOEqLXmloZ6EgVnjQ7/ttys7VFITB3mazzFiyQuKf4J6+b/a/Y";


        // Change FeatureLogin to static to allow calling from static Main
        static void FeatureLogin()
        {
            HaspFeature feature = HaspFeature.Default;

            string scope =
            "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>" +
            "<haspscope/>";

            Console.WriteLine("Enter the feature number to login (e.g., 1, 2, 3): ");
            string featureInput = Console.ReadLine();
            if (!int.TryParse(featureInput, out int featureNumber))
            {
                Console.WriteLine("Invalid feature number!");
                return;
            }
            feature = HaspFeature.FromFeature(featureNumber);

            hasp = new Hasp(feature);
            HaspStatus status = hasp.Login(vendorCode, scope);

            if (HaspStatus.StatusOk != status)
            {
                Console.WriteLine("Login failed: " + status);
            }
            else
            {
                Console.WriteLine("Login successful!");
            }
        }

        static void FeatureLogout()
        {
            HaspStatus status = hasp.Logout();
            if (HaspStatus.StatusOk != status)
            {
                Console.WriteLine("Logout failed: " + status);
            }
            else
            {
                Console.WriteLine("Logout successful!");
            }
        }

        static void GetFingerprint()
        {
            string scope =
                            "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>" +
                            "<haspscope/>";

            string format =
            "<haspformat format=\"host_fingerprint\"/>";
            string info = null;
            HaspStatus status = Hasp.GetInfo(scope, format, vendorCode, ref info);

            if (HaspStatus.StatusOk != status)
            {
                Console.WriteLine("GetFingerprint failed: " + status);
            }
            else
            {
                string filePath = "fingerprint.c2v";
                File.WriteAllText(filePath, info);
                Console.WriteLine("File saved with name: " + filePath);
            }   
            
        }

        static void ApplyV2CP()
        {
            Console.WriteLine("Enter the path to the .v2cp file: ");
            string v2cFilePath = Console.ReadLine();
            if (!File.Exists(v2cFilePath))
            {
                Console.WriteLine("The specified .v2c file does not exist.");
                return;
            }
            string v2cContent = File.ReadAllText(v2cFilePath);
            string ack = null;
            HaspStatus status = Hasp.Update(v2cContent, ref ack);
            if (HaspStatus.StatusOk != status)
            {
                Console.WriteLine("ApplyV2CP failed: " + status);
            }
            else
            {
                Console.WriteLine("ApplyV2CP successful!");
            }
        }

        static void GetSessionInfo()
        {
            string info = null;
            HaspStatus status = hasp.GetSessionInfo(Hasp.SessionInfo, ref info);
            if (HaspStatus.StatusOk != status)
            {
                Console.WriteLine("GetSessionInfo failed: " + status);
            }
            else
            {
                Console.WriteLine("Session Info:\n" + info);
            }
        }

        static void ReadMemory()
        {
            HaspFile file = hasp.GetFile(HaspFileId.ReadWrite);
            int size = 48;
            byte[] data = new byte[size];
            HaspStatus status = file.Read(data, 0, data.Length);

            if (HaspStatus.StatusOk != status)
            {
                Console.WriteLine("ReadMemory failed: " + status);
            }
            else
            {
                string text = System.Text.Encoding.ASCII.GetString(data);
                Console.WriteLine("Memory Read Successful! Data: " + text);                
            }            
        }

        static void WriteMemory()
        {
            HaspFile file = hasp.GetFile(HaspFileId.ReadWrite);
            Console.Write("Enter data: ");
            string input = Console.ReadLine();

            byte[] data = new byte[48];
            byte[] inputBytes = Encoding.ASCII.GetBytes(input);

            Array.Copy(inputBytes, data,
            Math.Min(inputBytes.Length, data.Length));

            HaspStatus status = file.Write(data, 0, data.Length);

            if (HaspStatus.StatusOk != status)
            {
                //handle error
                Console.WriteLine("WriteMemory failed: " + status);
            }
            else
            {
                Console.WriteLine("Memory Write Successful!");
            }
        }

        public static void Main(string[] args)
        {
            int choice;

            // The do-while loop ensures the menu runs at least once
            do
            {
                // Display the menu
                Console.WriteLine("\n--- Sentinel LDK Operations ---\n");
                Console.WriteLine("1. Login");
                Console.WriteLine("2. Logout");
                Console.WriteLine("3. Get Fingerprint");
                Console.WriteLine("4. Apply V2CP");
                Console.WriteLine("5. Get Session Info");
                Console.WriteLine("6. Read Memory");
                Console.WriteLine("7. Write Memory");
                Console.WriteLine("9. Exit");
                Console.Write("Enter your choice (1-7, 9 to exit): ");
                if (!int.TryParse(Console.ReadLine(), out choice))
                {
                    Console.WriteLine("Invalid input! Please enter a number.");
                    choice = 0; // Set to an invalid choice to trigger the default case
                }

                // Perform operation based on the selected number
                switch (choice)
                {
                    case 1:
                        FeatureLogin();
                        break;
                    case 2:
                        FeatureLogout();
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
                        ReadMemory();
                        break;
                    case 7:
                        WriteMemory();
                        break;
                    case 9:
                        Console.WriteLine("Exiting the program. Goodbye!\n");
                        break;
                    default:
                        Console.WriteLine("Invalid choice! Please select a number between 1 and 4.\n");
                        break;
                }

            } while (choice != 9); // The loop continues until the user inputs 9    
        }
    }
}