// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

import "../tokens/nf-token-metadata.sol";
import "../ownership/ownable.sol";

contract MyArtSale is NFTokenMetadata, Ownable {

    constructor() {
        nftName = "";
        nftSymbol = "";
    }

    function mint(
        address _to,
        uint256 _tokenId,
        string calldata _uri
    )
    external onlyOwner
    {
        super._mint(_to, _tokenId);
        super._setTokenUri(_tokenId, _uri);
    }
}
