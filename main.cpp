#include <QCoreApplication>
#include <cstdio>
#include <unistd.h>
#include "DeckLinkAPI.h"

void showHelp(char* appName);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    char	*appName = argv[0];
    int		ch;
    int64_t	ports = -1;
    int		inputPort = -1;
    bool	displayHelp = false;
    bool	listAttributes = false;
    bool	saveConfig = false;

    HRESULT					result;
    IDeckLinkIterator		*deckLinkIterator;
    IDeckLink				*deckLink;
    IDeckLinkInput			*deckLinkInput = NULL;
    IDeckLinkAttributes     *deckLinkAttributes = NULL;
    IDeckLinkConfiguration	*deckLinkConfiguration = NULL;


    if ( argc == 1 )
        displayHelp = true;

    while ((ch = getopt(argc, argv, "?hlp:s")) != -1)
    {
        switch (ch)
        {
            case 'l':
                printf("List Attributes\n");
                listAttributes = true;
                break;

            case 'p':
                inputPort = atoi(optarg);
                printf("Configure Input port to %d\n", inputPort);
                break;

            case 's':
                saveConfig = true;
                break;

            case '?':
            case 'h':
            default:
                displayHelp = true;
        }
    }

    if (displayHelp )
    {
        showHelp(appName);
        exit(0);
    }

    // Create an IDeckLinkIterator object to enumerate all DeckLink cards in the system
    deckLinkIterator = CreateDeckLinkIteratorInstance();
    if (deckLinkIterator == NULL)
    {
        fprintf(stderr, "A DeckLink iterator could not be created (DeckLink drivers may not be installed).\n");
        exit(1);
    }

    int dnum = 0;
    deckLink = NULL;

    while (deckLinkIterator->Next(&deckLink) == S_OK)
    {
        if (0 != dnum)
        {
            dnum++;
            // Release the IDeckLink instance when we've finished with it to prevent leaks
            deckLink->Release();
            continue;

        }
        dnum++;

        // Query the DeckLink for its configuration interface
        result = deckLink->QueryInterface(IID_IDeckLinkInput, (void**)&deckLinkInput);
        if (result != S_OK)
        {
            fprintf(stderr, "Could not obtain the IDeckLinkInput interface - result = %08x\n", result);
            exit(result);
        }

        // Query the DeckLink for its configuration interface
        result = deckLinkInput->QueryInterface(IID_IDeckLinkConfiguration, (void**)&deckLinkConfiguration);
        if (result != S_OK)
        {
            fprintf(stderr, "Could not obtain the IDeckLinkConfiguration interface: %08x\n", result);
            exit(result);
        }

        if ( listAttributes )
        {
            // Query the DeckLink for its attributes interface
            result = deckLink->QueryInterface(IID_IDeckLinkAttributes, (void**)&deckLinkAttributes);
            if (result != S_OK)
            {
                fprintf(stderr, "Could not obtain the IDeckLinkAttributes interface - result = %08x\n", result);
                exit(result);
            }

            int	itemCount = 0;
            result = deckLinkAttributes->GetInt(BMDDeckLinkVideoInputConnections, &ports);
            if (result == S_OK)
            {
                printf("Available Input Port Id's:\n");
                if (ports & bmdVideoConnectionSDI)
                {
                    itemCount++;
                    printf("(%d) SDI", bmdVideoConnectionSDI);
                }

                if (ports & bmdVideoConnectionHDMI)
                {
                    if (itemCount++ > 0)
                        printf(", ");
                    printf("(%d) HDMI", bmdVideoConnectionHDMI);
                }

                if (ports & bmdVideoConnectionOpticalSDI)
                {
                    if (itemCount++ > 0)
                        printf(", ");
                    printf("(%d) Optical SDI", bmdVideoConnectionOpticalSDI);
                }

                if (ports & bmdVideoConnectionComponent)
                {
                    if (itemCount++ > 0)
                        printf(", ");
                    printf("(%d) Component", bmdVideoConnectionComponent);
                }

                if (ports & bmdVideoConnectionComposite)
                {
                    if (itemCount++ > 0)
                        printf(", ");
                    printf("(%d) Composite", bmdVideoConnectionComposite);
                }

                if (ports & bmdVideoConnectionSVideo)
                {
                    if (itemCount++ > 0)
                        printf(", ");
                    printf("(%d) S-Video", bmdVideoConnectionSVideo);
                }
            }
            else
            {
                fprintf(stderr, "Could not obtain the list of input ports - result = %08x\n", result);
                exit(result);
            }
            printf("\n");

        }

        /* Current port setting */
        result = deckLinkConfiguration->GetInt(bmdDeckLinkConfigVideoInputConnection, &ports);
        if (result != S_OK)
        {
            fprintf(stderr, "Couldn't GetVideoInput \n");
            exit(result);
        }

        result = deckLinkConfiguration->GetInt(bmdDeckLinkConfigVideoInputConnection, &ports);
        printf("Current port: %ld\n", ports);

        if (inputPort >= 0 )
        {
            printf("Setting input port to %d\n", inputPort);
            if ( (result=deckLinkConfiguration->SetInt(bmdDeckLinkConfigVideoInputConnection, inputPort)) != S_OK )
            {
                printf("Couldn't set input port to %d\n\n", inputPort);
                showHelp(appName);
            }
            if ( saveConfig )
            {
                printf("Saving configuration ...\n");
                if ( (result=deckLinkConfiguration->WriteConfigurationToPreferences()) == S_OK )
                {
                    printf("New configuration saved\n");
                }
                else
                {
                    printf("Couldn't save configuration\n");
                    exit(result);
                }
            }
        }
        exit(result);

    }

    return a.exec();
}

void showHelp(char *appName)
{
    printf("Usage:\n");
    printf("%s [-l] [-p portId] [-s]\n", appName);
    printf("\t-l           List current configuration\n");
    printf("\t-p portId    Set input port to one of those listed by the -l option\n");
    printf("\t-s           Save configuration across reboots\n");
}
